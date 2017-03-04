#pragma once

#include <memory>

class Window;
typedef std::shared_ptr<Window> WindowPtr;

class Texture2D;
typedef std::shared_ptr<Texture2D> TexturePtr;

class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

class Mesh;
typedef std::shared_ptr<Mesh> MeshPtr;

struct Vertex;
typedef std::shared_ptr<Vertex> VertexPtr;

class Model;
typedef std::shared_ptr<Model> ModelPtr;

struct Material;
typedef std::shared_ptr<Material> MaterialPtr;