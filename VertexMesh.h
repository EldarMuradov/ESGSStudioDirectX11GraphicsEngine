#pragma once
#include "Vector2D.h"
#include "Vector3D.h"

class VertexMesh
{
public:
	VertexMesh() : m_position(), m_texcoord()
	{
	}
	VertexMesh(Vector3D pos, Vector2D tex) : m_position(pos), m_texcoord(tex)
	{
	}
	VertexMesh(const VertexMesh& vertex_mesh) : m_position(vertex_mesh.m_position), m_texcoord(vertex_mesh.m_texcoord)
	{
	}

	~VertexMesh()
	{
	}

public:
	Vector3D m_position;
	Vector2D m_texcoord;
};