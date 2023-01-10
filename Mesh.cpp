#define TINYOBJLOADER_IMPLEMENTATION

#include "Mesh.h"
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>
#include "GraphicsEngine.h"
#include "VertexMesh.h"



Mesh::Mesh(const wchar_t* full_path): Resource(full_path)
{
	tinyobj::attrib_t attrib_ts;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warnings;
	std::string errors;

	std::string inputFile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

	bool res = tinyobj::LoadObj(&attrib_ts, &shapes, &materials, &warnings, &errors, inputFile.c_str());

	if(!errors.empty() || !res)
		throw std::exception("Failed to create {Mesh}. Error in ctor.");

	if(shapes.size() > 1)
		throw std::exception("Failed to create {Mesh}. Error in ctor.");

	std::vector<VertexMesh> vertex_meshes;

	std::vector<unsigned int> indices;

	for (size_t size = 0; size < shapes.size(); size++)
	{
		size_t index_offset = 0;
		vertex_meshes.reserve(shapes[size].mesh.indices.size());
		indices.reserve(shapes[size].mesh.indices.size());

		for (size_t face = 0; face < shapes[size].mesh.num_face_vertices.size(); face++)
		{
			unsigned char num_face = shapes[size].mesh.num_face_vertices[face];

			for (unsigned char vertice = 0; vertice < num_face; vertice++)
			{
				tinyobj::index_t index = shapes[size].mesh.indices[index_offset + vertice];

				tinyobj::real_t vx = attrib_ts.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attrib_ts.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attrib_ts.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attrib_ts.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attrib_ts.texcoords[index.texcoord_index * 2 + 1];

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));

				vertex_meshes.push_back(vertex);

				indices.push_back(index_offset + vertice);
			}

			index_offset += num_face;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getVertexMeshLayoutByteCodeAndSize(&shader_byte_code, &size_shader);

	m_vertex_buffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&vertex_meshes[0], sizeof(VertexMesh), (UINT)vertex_meshes.size(), shader_byte_code, (UINT)size_shader);

	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&indices[0], (UINT)indices.size());
}

Mesh::~Mesh()
{

}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return m_index_buffer;
}
