#include "model_loader.hpp"

ModelLoader::ModelLoader() {
    this->config.mtl_search_path = "./";
}


RenderComponent ModelLoader::load(std::string file_path) {
    if (!this->reader.ParseFromFile(file_path, this->config)) {
        if (!this->reader.Error().empty()) {
            std::cout << "TinyObjLoader: " << this->reader.Error() << std::endl;
        }
        exit(1);
    }


    if (!this->reader.Warning().empty()) {
        std::cout << "TinyObjLoader: " << this->reader.Warning() << std::endl;
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    std::vector<float> vertices;

    // s: shape index
    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        // f: face index
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            // fv: vertex per face< in this case == 3
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            assert(fv == 3);

            // loop over vertices in the face
            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                // Position
                vertices.push_back(attrib.vertices[3 * static_cast<size_t>(idx.vertex_index) + 0]);
                vertices.push_back(attrib.vertices[3 * static_cast<size_t>(idx.vertex_index) + 1]);
                vertices.push_back(attrib.vertices[3 * static_cast<size_t>(idx.vertex_index) + 2]);

                // UV
                assert(idx.texcoord_index >= 0);
                if (idx.texcoord_index >= 0) {
                    vertices.push_back(attrib.texcoords[2 * static_cast<size_t>(idx.texcoord_index) + 0]);
                    vertices.push_back(attrib.texcoords[2 * static_cast<size_t>(idx.texcoord_index) + 1]);
                }

                // Normal
                assert(idx.normal_index >= 0);
                if (idx.normal_index >= 0) {
                    vertices.push_back(attrib.normals[3 * static_cast<size_t>(idx.normal_index) + 0]);
                    vertices.push_back(attrib.normals[3 * static_cast<size_t>(idx.normal_index) + 1]);
                    vertices.push_back(attrib.normals[3 * static_cast<size_t>(idx.normal_index) + 2]);
                }

            }
            index_offset += fv;
        }
    }

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    RenderComponent render{};
    render.VAO = vao;
    render.vertexCount = vertices.size() / 8;
    return render;


}

void ModelLoader::set_texture(RenderComponent &render_component, std::string texture_path) {
    render_component.material = make_texture(texture_path.c_str());
}

unsigned int ModelLoader::make_texture(const char* filename) {

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(
        filename, &width, &height, &channels, STBI_rgb_alpha);

	//make the texture
    unsigned int texture;
	glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //load data
    glTexImage2D(GL_TEXTURE_2D,
        0, GL_RGBA, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    //free data
	stbi_image_free(data);

    //Configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}
