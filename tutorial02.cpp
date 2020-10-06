#include "Sphere.h"
#include <algorithm>
#include <Windows.h>
#include "AudioFile.h"

AudioFile<double> audio;

GLuint programID;
GLFWwindow* window;
GLuint VertexArrayID;
// Get a handle for our "MVP" uniform
GLuint MatrixID;
GLuint ViewMatrixID;
GLuint ModelMatrixID;
// Get a handle for our buffers
GLuint vertexID;
GLuint normalID;
GLuint LightID;
GLuint LightPowID;
GLuint BategID;


struct Light{
	vec3 position;
	vec3 intensities; //a.k.a. the color of the light
};

Light gLight;


const bool operator<(const vec3&lhs, const vec3&rhs) {
	// Sort in ascending order by key x, y priority
	if (lhs.x == rhs.x)
	{
		if (lhs.y == rhs.y)
			return lhs.z < rhs.z;
		return lhs.y < rhs.y;
	}
	return lhs.x < rhs.x;
}
float profZ = 30;
void modelTransform(vec3 posicioCentre, float rotax, float rotay, float Sc)
{
		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);
		glm::mat4 ViewMatrix = glm::lookAt(
			glm::vec3( 0, 0, profZ), // Camera is here
			glm::vec3( 0, 0, 0 ), // and looks here
			glm::vec3( 0, 1, 0 )  // Head is up (set to 0,-1,0 to look upside-down)
		);
 		glm::mat4 RotationMatrix = rotate(rotate(mat4(1.0), rotax, vec3(1, 0, 0)), rotay, vec3(0,1,0));
		glm::mat4 TranslationMatrix = translate(mat4(1.0), posicioCentre); // A bit to the left
		glm::mat4 ScalingMatrix = scale(mat4(), vec3(Sc/10, Sc/10, Sc/10));
		glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;

		glm::mat4 TG = ProjectionMatrix * ViewMatrix * ModelMatrix;
	//TG = translate(TG, posicioCentre);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &TG[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

}
int channel = 0;
int numSamples;

int setup()
{
	audio.load("./SongTryN3.wav");
	numSamples = audio.getNumSamplesPerChannel();

	/*for (int i = 0; i < numSamples; i++)
	{
		cout<<audio.samples[channel][i]<<endl;
	}*/
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "TG");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Get a handle for our buffers
	vertexID = glGetAttribLocation(programID, "vertex");
	normalID = glGetAttribLocation(programID, "vertNormal");
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	LightPowID = glGetUniformLocation(programID, "LightPow");
	BategID = glGetUniformLocation(programID, "Bateg");
	return 0;
}


int main(void)
{
	if (setup() != 0) return -1;
	CPoint center;


	gLight.position = vec3(4, 4, 4);
	gLight.intensities = glm::vec3(0,0,0); //white
	
	Sphere sp;
	sp.ini(4, 200, vec3(0.0, 0.0, 0.0));
	sp.PointsSphere();
	sort(sp.points.begin(), sp.points.end(),
		[](const CPoint &lhs, const CPoint &rhs) {
		if (lhs.p.x == rhs.p.x)
		{
			if (lhs.p.y == rhs.p.y)
				return lhs.p.z < rhs.p.z;
			return lhs.p.y < rhs.p.y;
		}
		return lhs.p.x < rhs.p.x;
	});
	sp.constrLines(0.1, 0.1, 0.025);

	Sphere sp1;
	sp1.ini(3, 150, vec3(0.0, 0.0, 0.0));
	sp1.PointsSphere();
	sort(sp1.points.begin(), sp1.points.end(),
		[](const CPoint &lhs, const CPoint &rhs) {
		if (lhs.p.x == rhs.p.x)
		{
			if (lhs.p.y == rhs.p.y)
				return lhs.p.z < rhs.p.z;
			return lhs.p.y < rhs.p.y;
		}
		return lhs.p.x < rhs.p.x;
	});
	sp1.constrLines(0.06, 0.06, 0.025);

	Sphere sp2;
	sp2.ini(2, 100, vec3(0.0, 0.0, 0.0));
	sp2.PointsSphere();
	sort(sp2.points.begin(), sp2.points.end(),
		[](const CPoint &lhs, const CPoint &rhs) {
		if (lhs.p.x == rhs.p.x)
		{
			if (lhs.p.y == rhs.p.y)
				return lhs.p.z < rhs.p.z;
			return lhs.p.y < rhs.p.y;
		}
		return lhs.p.x < rhs.p.x;
	});
	sp2.constrLines(0.03, 0.03, 0.025);

	Sphere sp3;
	sp3.ini(1, 80, vec3(0.0, 0.0, 0.0));
	sp3.PointsSphere();
	sort(sp3.points.begin(), sp3.points.end(),
		[](const CPoint &lhs, const CPoint &rhs) {
		if (lhs.p.x == rhs.p.x)
		{
			if (lhs.p.y == rhs.p.y)
				return lhs.p.z < rhs.p.z;
			return lhs.p.y < rhs.p.y;
		}
		return lhs.p.x < rhs.p.x;
	});
	sp3.constrLines(0.01, 0.01, 0.025);
	for (int i = 0; i < sp1.renderPoints.size(); ++i)
	{
		sp.renderPoints.push_back(sp1.renderPoints[i]);
		sp.normalPoints.push_back(sp1.normalPoints[i]);
	}
	for (int i = 0; i < sp2.renderPoints.size(); ++i)
	{
		sp.renderPoints.push_back(sp2.renderPoints[i]);
		sp.normalPoints.push_back(sp2.normalPoints[i]);
	}
	for (int i = 0; i < sp3.renderPoints.size(); ++i)
	{
		sp.renderPoints.push_back(sp3.renderPoints[i]);
		sp.normalPoints.push_back(sp3.normalPoints[i]);
	}
	GLuint VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	GLuint normalbuffer1;

	GLuint vertexbuffer1;
	glGenBuffers(1, &normalbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*sp.normalPoints.size(), &sp.normalPoints[0], GL_STATIC_DRAW);
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*sp.renderPoints.size(), &sp.renderPoints[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vertexID, 3, GL_FLOAT, GL_FALSE, 0, 0);


	float y = 0;
	float rotX = 0, rotY = 0, Sc = 10;
	glm::vec3 lightPos;
	float bateg = 0, sumBateg = 0;
	float lim = 10;
	int audioi = 0;

	double lastTime = glfwGetTime();
	float FrameRate = 44.12, framecount = 0;
	int distort = 0;
	do {
		// Measure speed
		double currentTime = glfwGetTime();
		audioi += audio.getSampleRate() / FrameRate ;
		float sample = audio.samples[channel][audioi% audio.samples[0].size()];
		float bategVal = pow(sin(bateg), 33) * sin(bateg + 1.5) * 8 + pow(cos(bateg), 33) * cos(bateg + 1.5) * 8;
		float samplePower = pow(sample * 10, 5) / 500;
		if (samplePower > 3) samplePower = 3;
		glUniform1f(BategID, + samplePower + bategVal);
		/*cout << sample << ' ' << audioi << ' ' << audio.samples[0].size() << endl;
		cout << FrameRate << ' ' << audio.getSampleRate() / FrameRate << ' ' << float(audioi)/audio.samples[0].size()*266.48<<endl;*/
		cout << glfwGetTime() << ' '<< float(audioi) / audio.samples[0].size()*266.48 << endl;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			//cout<<FrameRate<<' '<< audio.getSampleRate() / FrameRate <<endl;
			FrameRate= framecount;
			framecount = 0;
			lastTime += 1.0;
		}
		framecount++;
		//lightPos = glm::vec3(7*cos(3.14*y/180), 0, 7*sin(3.14*y/360));
		if (GetKeyState('L') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			lightPos = vec3(float(rand() % 100 - 50) / 100, float(rand() % 100 - 50) / 100, float(rand() % 100 - 50) / 100);
			lightPos *= 10;
			y = 1;
		}
		else if (GetKeyState('C') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{ 
			lightPos = vec3(0,0,0);
			lightPos *= 10;
			y = 1;
		}
		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			rotY -= 3.14 / 20;
		if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			rotY += 3.14 / 20;
		if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			rotX -= 3.14 / 20;
		if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			rotX += 3.14 / 20;
		if (GetKeyState('U') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (profZ == 10) {
				Sc *= 1.1*1.1;
				bateg -= sumBateg;
			}
			else if (profZ > 10) profZ -= 1;
			if (profZ < 10) profZ = 10;

		}
		else if (GetKeyState('J') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (Sc > 10) Sc /= 1.1*1.1;
			else if (profZ < 100) {
				profZ += 1;
				bateg -= sumBateg;
			}
		}
		if (GetKeyState('I') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (profZ == 10) {
				Sc *= 1.1;
				bateg -= sumBateg;
			}
			else if (profZ > 10) profZ -= 0.5;
			if (profZ < 10) profZ = 10;

		}
		else if (GetKeyState('K') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (Sc > 10 ) Sc /= 1.1;
			else if (profZ < 100) {
				profZ += 0.5;
				bateg -= sumBateg;
			}
		}
		if (GetKeyState('F') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			sumBateg += 0.01;
		if (GetKeyState('V') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			sumBateg -= 0.01;
		if (GetKeyState('P') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			lim++;
		if (GetKeyState('O') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			lim--;
		if (sample > 0.6 || (audioi > audio.samples[0].size() / 2 && sample > 0.3))
			distort = 0;
		if ( distort < 10 || GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (y == 1) y = 10;
			glUniform3f(glGetUniformLocation(programID, "rand"), float(rand() % 255) / 2550, float(rand() % 255) / 2550, float(rand() % 255) / 2550);
		}
		else
		{
			glUniform3f(glGetUniformLocation(programID, "rand"), 0, 0, 0);
			bateg += sumBateg;
		}
		if (y > lim) y = lim;
		if (lim < 1) lim = 1;
		if (Sc < 1) Sc = 1;
		if (Sc > 1000000) Sc /= pow(1.1,121);
		if (sumBateg < 0) sumBateg = 0;
		if (sumBateg > 1) sumBateg = 1;
		distort++;
		//lightPos *= Sc;
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
		//lightPos /= Sc;
		glUniform1f(LightPowID, y);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		glEnableVertexAttribArray(normalID);
		glEnableVertexAttribArray(vertexID);

		int zoom = int(log10(Sc));
		for (int i = zoom; i < 4+zoom; ++i){
			modelTransform(vec3(0, 0, 0), rotX, rotY, 10*Sc / int(pow(10,i )));
			glDrawArrays(GL_TRIANGLES, 0, sp.renderPoints.size() / 3);
			//cout << i << endl;
		}

		/*for (int i = 0; i < sp.renderPoints.size() / 3; i+=3)
		{
			
			if (y * 1000 < i) i = sp.renderPoints.size();
		}*/
		y+= 1;
		//if (y > sp.renderPoints.size() / 3) y = sp.renderPoints.size() / 3;
		glDisableVertexAttribArray(normalID);
		glDisableVertexAttribArray(vertexID);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		y++;
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO

	glDeleteBuffers(1, &vertexbuffer1);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

