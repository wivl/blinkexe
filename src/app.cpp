#include "app.hpp"

App::App() {
    set_up_glfw();
}

App::~App() {
    glDeleteProgram(shader);
    delete motion_system;
    delete camera_system;
    delete render_system;
    glfwTerminate();
}

void App::run() {
	float currentTime, deltaTime, lastTime;
    while (!glfwWindowShouldClose(window)) {
    	currentTime = static_cast<float>(glfwGetTime());
    	deltaTime = currentTime - lastTime;
    	lastTime = currentTime;

    	// 更新 motion system
        motion_system->update(transform_components, physics_components, deltaTime);
    	// 更新 camera system
        bool should_close = camera_system->update(transform_components, cameraID, *camera_component, deltaTime);
		if (should_close) {
			break;
		}
    	// 更新 render system
		render_system->update(transform_components, render_components);
	}
}

void App::set_up_glfw() {

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(BLINK_WINDOW_WIDTH, BLINK_WINDOW_HEIGHT, BLINK_WINDOW_NAME, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}

}

void App::set_up_opengl() {

    glClearColor(0.375f, 0.375f, 0.375f, 0.0f);
	//Set the rendering region to the actual screen size
	int w,h;
	glfwGetFramebufferSize(window, &w, &h);
	//(left, top, width, height)
	glViewport(0,0,w,h);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    shader = make_shader(
		"../src/shaders/default.vert",
		"../src/shaders/default.frag");

    glUseProgram(shader);
	// 投影矩阵，不依赖于摄像机
	unsigned int projLocation = glGetUniformLocation(shader, "projection");
	glm::mat4 projection = glm::perspective(
		45.0f, static_cast<float>(BLINK_WINDOW_WIDTH) / static_cast<float>(BLINK_WINDOW_HEIGHT), 0.1f, 100.0f);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void App::make_systems() {
    motion_system = new MotionSystem();
    camera_system = new CameraSystem(shader, window);
    render_system = new RenderSystem(shader, window);
}