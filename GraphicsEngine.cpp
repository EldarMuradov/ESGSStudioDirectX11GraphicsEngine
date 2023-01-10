#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) 
	{ 
		throw std::exception("Failed to create {RenderSystem}. Error in {GraphicsEngine::ctor}.");
	}

	try
	{
		m_tex_manager = new TextureManager();
	}
	catch (...) 
	{ 
		throw std::exception("Failed to create {TextureManager}. Error in {GraphicsEngine::ctor}.");
	}

	try
	{
		m_mesh_manager = new MeshManager();
	}
	catch (...)
	{
		throw std::exception("Failed to create {MeshManager}. Error in {GraphicsEngine::ctor}.");
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	m_render_system->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	m_render_system->releaseCompiledShader();
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

void GraphicsEngine::getVertexMeshLayoutByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_mesh_manager;
	delete m_tex_manager;
	delete m_render_system;
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) 
		throw std::exception("Failed to create {GraphicsEngine}. Error in {GraphicsEngine::create()}.");
	GraphicsEngine::m_engine = new GraphicsEngine();
}

void GraphicsEngine::release() 
{
	if (!GraphicsEngine::m_engine) 
		return;
	delete GraphicsEngine::m_engine;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}
