#pragma once

#include <memory>

typedef unsigned int uint;
typedef unsigned char ubyte;
typedef char byte;

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

class Camera;
typedef std::shared_ptr<Camera> CameraPtr;

class FrameBuffer;
typedef std::shared_ptr<FrameBuffer> FrameBufferPtr;

class PostProcessor;
typedef std::shared_ptr<PostProcessor> PostProcessorPtr;

class PostProcessEffect;
typedef std::shared_ptr<PostProcessEffect> PostProcessEffectPtr;