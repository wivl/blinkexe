#include "app.hpp"

unsigned int make_module(const std::string& filepath, unsigned int module_type) {
	std::ifstream file;
	std::stringstream buffered_lines;
	std::string line;

	file.open(filepath);
	while (std::getline(file, line)) {
		buffered_lines << line << "\n";
	}
	std::string shader_source{ buffered_lines.str() };
	const char* shader_source_c_str{ shader_source.c_str() };
	buffered_lines.str("");
	file.close();

	unsigned int shader_module{ glCreateShader(module_type) };
	glShaderSource(shader_module, 1, &shader_source_c_str, nullptr);
	glCompileShader(shader_module);

	int success;
	glGetShaderiv(shader_module, GL_COMPILE_STATUS, &success);
	if (!success) {
		char error_log[1024];
		glGetShaderInfoLog(shader_module, 1024, nullptr, error_log);
		std::cout << "Shader Module compilation error:" << std::endl << error_log << std::endl;
	}
	return shader_module;
}


unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
	std::vector<unsigned int> modules;
	modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
	modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

	unsigned int shader{ glCreateProgram() };
	for (unsigned int shader_module : modules) {
		glAttachShader(shader, shader_module);
	}
	glLinkProgram(shader);

	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char error_log[1024];
		glGetProgramInfoLog(shader, 1024, nullptr, error_log);
		std::cout << "Shader Linking error:" << std::endl << error_log << std::endl;
	}
	for (unsigned int shader_module : modules) {
		glDeleteShader(shader_module);
	}
	return shader;
}

App::App() {
	setup_glfw();
}

App::~App() {
	glDeleteBuffers(vbos.size(), vbos.data());
	glDeleteVertexArrays(vaos.size(), vaos.data());
	glDeleteTextures(textures.size(), textures.data());
	glDeleteProgram(shader);

	glfwTerminate();
}

unsigned int App::make_entity() {
	return entity_count++;
}

unsigned int App::make_cube_mesh(glm::vec3 size) {
	float l = size.x;
	float w = size.y;
	float h = size.z;

	std::vector<float> vertices = {
		 l,  w, -h, 1.0f, 1.0f,
		 l, -w, -h, 1.0f, 0.0f,
		-l, -w, -h, 0.0f, 0.0f,
		-l, -w, -h, 0.0f, 0.0f,
		-l,  w, -h, 0.0f, 1.0f,
		 l,  w, -h, 1.0f, 1.0f,

		-l, -w,  h, 0.0f, 0.0f,
		 l, -w,  h, 1.0f, 0.0f,
		 l,  w,  h, 1.0f, 1.0f,
		 l,  w,  h, 1.0f, 1.0f,
		-l,  w,  h, 0.0f, 1.0f,
		-l, -w,  h, 0.0f, 0.0f,

		-l,  w,  h, 1.0f, 1.0f,
		-l,  w, -h, 1.0f, 0.0f,
		-l, -w, -h, 0.0f, 0.0f,
		-l, -w, -h, 0.0f, 0.0f,
		-l, -w,  h, 0.0f, 1.0f,
		-l,  w,  h, 1.0f, 1.0f,

		 l, -w, -h, 0.0f, 0.0f,
		 l,  w, -h, 1.0f, 0.0f,
		 l,  w,  h, 1.0f, 1.0f,
		 l,  w,  h, 1.0f, 1.0f,
		 l, -w,  h, 0.0f, 1.0f,
		 l, -w, -h, 0.0f, 0.0f,

		-l, -w, -h, 0.0f, 0.0f,
		 l, -w, -h, 1.0f, 0.0f,
		 l, -w,  h, 1.0f, 1.0f,
		 l, -w,  h, 1.0f, 1.0f,
		-l, -w,  h, 0.0f, 1.0f,
		-l, -w, -h, 0.0f, 0.0f,

		 l,  w,  h, 1.0f, 1.0f,
		 l,  w, -h, 1.0f, 0.0f,
		-l,  w, -h, 0.0f, 0.0f,
		-l,  w, -h, 0.0f, 0.0f,
		-l,  w,  h, 0.0f, 1.0f,
		 l,  w,  h, 1.0f, 1.0f
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	vaos.push_back(VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	vbos.push_back(VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
		vertices.data(), GL_STATIC_DRAW);
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
	glEnableVertexAttribArray(0);
	//texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
	glEnableVertexAttribArray(1);

	return VAO;
}

unsigned int App::make_texture(std::string filename) {
	int width, height, channels;
	
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	unsigned int texture;
	glGenTextures(1, &texture);
	textures.push_back(texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return texture;
}


void App::run() {
	while (!glfwWindowShouldClose(window)) {
#ifdef BLINK_DEBUG
		std::cout << "[DEBUG]BLINK: Frame # " << ++frame << std::endl;
#endif
		bool should_close{ camera_system->update(transform_components, camera_id, *camera_component, 16.67f / 1000.0f) };
		if (should_close) {
			break;
		}
		render_system->update(transform_components, render_components);
	}
}

void App::setup_glfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(BLINK_WINDOW_WIDTH, BLINK_WINDOW_HEIGHT, BLINK_WINDOW_NAME, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load OpenGL" << std::endl;
	}
	glfwTerminate();
}

void App::setup_opengl() {
	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// TODO: 
	shader = make_shader("../src/shaders/default.vert", "../src/shaders/default.frag");

	glUseProgram(shader);
	unsigned int projLocation = glGetUniformLocation(shader, "projection");
	glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 10.0f);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void App::make_systems() {
	camera_system = std::make_shared<CameraSystem>(shader, window);
	render_system = std::make_shared<RenderSystem>(shader, window);
}
