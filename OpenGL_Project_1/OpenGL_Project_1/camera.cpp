#include "camera.h"
#include <limits>
#include "GLFW/glfw3.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#define   FloatInfinity std::numeric_limits<float>::infinity()
#define   SQRT1_2  0.7071067811865476

namespace cameraControl
{
	uint32_t trackball::m_keys[3] = { 65 /*A*/, 83 /*S*/, 68 /*D*/ };
	static trackball* s_instance = nullptr;

	camera::camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_eye = pos;
		m_viewMatr = glm::mat4(1.0f);
		m_up = glm::vec3(0, 1, 0);
	}

	void camera::LookAt(const glm::vec3& m_target) {
		m_viewMatr = glm::lookAt(m_eye, m_target, m_up);
	}

	trackball::trackball(camera* cam, glm::vec4 screenSize)
	{
		this->m_pCam = cam;
		this->m_screen = screenSize;
		this->m_enabled = true;
		this->m_rotateSpeed = 1.0f;
		this->m_zoomSpeed = 1.2f;
		this->m_panSpeed = 0.3f;
		this->m_noRotate = false;
		this->m_noPan = false;
		this->m_noZoom = false;
		this->m_noRoll = false;
		this->m_staticMoving = false;
		this->m_dynamicDampingFactor = 0.2f;
		this->m_minDistance = 0.0f;
		this->m_maxDistance = FloatInfinity;
		this->m_target = glm::vec3(0.0);
		this->m_lastPos = glm::vec3(0.0);
		this->m_state = TCB_STATE::NONE;
		this->m_prevState = TCB_STATE::NONE;
		this->m_eye = glm::vec3(0.0);
		this->m_rotStart = glm::vec3(0.0);
		this->m_rotEnd = glm::vec3(0.0);
		this->m_zoomStart = glm::vec2(0.0);
		this->m_zoomEnd = glm::vec2(0.0);
		this->m_panStart = glm::vec2(0.0);
		m_panEnd = glm::vec2(0.0);
	}

	trackball& trackball::GetInstance(camera* cam, glm::vec4 screenSize) 
	{
		static trackball instance(cam, screenSize);
		s_instance = &instance;
		return instance;
	}

	//------------------------   Static callbacks -------------------------------------------------
	static void MouseButtonCallBack(GLFWwindow* win, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(win, &xpos, &ypos);
			s_instance->MouseDown(button, action, mods, (int)xpos, (int)ypos);
		}
		if (action == GLFW_RELEASE) {
			s_instance->MouseUp();
		}

	}
	static void MouseMoveCallBack(GLFWwindow* win, double xpos, double ypos) {

		s_instance->MouseMove((int)xpos, (int)ypos);

	}
	static void MouseScrollCallBack(GLFWwindow* win, double xpos, double ypos) {

		s_instance->MouseWheel(xpos, ypos);

	}

	static void KeyboardCallBack(GLFWwindow* win, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			s_instance->KeyDown(key);
		}
		if (action == GLFW_RELEASE) {
			s_instance->KeyUp();
		}

	}
	//-----------------------------------------------------------------------------------------------


	void trackball::Init(window* win) 
	{
		glfwSetCursorPosCallback(win->MainWindow, &MouseMoveCallBack);
		glfwSetMouseButtonCallback(win->MainWindow, &MouseButtonCallBack);
		glfwSetScrollCallback(win->MainWindow, &MouseScrollCallBack);
		glfwSetKeyCallback(win->MainWindow, &KeyboardCallBack);
	}

	void trackball::Update() {
		//   _eye.setFrom( object.position ).sub( target );
		m_eye = m_pCam->m_eye - m_target;
		//m_eye -= m_eye  - m_target  ; // Vector3.Subtract(_eye, _target);
		if (!m_noRotate)
		{
			RotateCamera();
		}

		if (!m_noZoom)
		{
			ZoomCamera();
		}

		if (!m_noPan)
		{
			PanCamera();
		}

		// object.position =  target + _eye;
		m_pCam->m_eye = (m_target + m_eye);
		CheckDistances();
		m_pCam->LookAt(m_target);
		// distanceToSquared
		if (glm::length2(m_lastPos - m_pCam->m_eye) > 0.0f)
		{
			m_lastPos = m_pCam->m_eye;
		}
	}

	void trackball::RotateCamera()
	{
		float angle = (float)acos(glm::dot(m_rotStart, m_rotEnd) / glm::length(m_rotStart) / glm::length(m_rotEnd));

		if (!isnan(angle) && angle != 0.0f)
		{
			glm::vec3 axis = glm::normalize(glm::cross(m_rotStart, m_rotEnd)); 

			if (glm::isnan(axis.x) || glm::isnan(axis.y) || glm::isnan(axis.z))
				return;
			glm::quat quaternion;// Quaternion quaternion = Quaternion.Identity;
			angle *= m_rotateSpeed;
			quaternion = glm::angleAxis(-angle, axis);
			m_eye = glm::rotate(quaternion, m_eye);
			m_pCam->m_up = glm::rotate(quaternion, m_pCam->m_up);
			m_rotEnd = glm::rotate(quaternion, m_rotEnd);
			if (m_staticMoving)
			{
				m_rotStart = m_rotEnd;
			}
			else
			{
				quaternion = glm::angleAxis(angle * (m_dynamicDampingFactor - 1.0f), axis);
				m_rotStart = glm::rotate(quaternion, m_rotStart);
			}
		}
	}

	void trackball::ZoomCamera()
	{
		float factor = 1.0f + (float)(m_zoomEnd.y - m_zoomStart.y) * m_zoomSpeed;
		if (factor != 1.0f && factor > 0.0f)
		{
			m_eye = m_eye * (float)factor;
			if (m_staticMoving)
			{
				m_zoomStart = m_zoomEnd;
			}
			else
			{
				m_zoomStart.y += (float)(m_zoomEnd.y - m_zoomStart.y) * m_dynamicDampingFactor;
			}
		}
	}

	void trackball::PanCamera()
	{
		glm::vec2 mouseChange = m_panEnd - m_panStart;
		if (glm::length(mouseChange) != 0.0f)
		{
			mouseChange *= glm::length(m_eye) * m_panSpeed;
			glm::vec3 pan = glm::normalize(glm::cross(m_eye, m_pCam->m_up));
			pan *= mouseChange.x;
			glm::vec3 camUpClone = glm::normalize(m_pCam->m_up);
			camUpClone *= mouseChange.y;
			pan += camUpClone;
			m_pCam->m_eye += pan;
			m_target += pan;
			if (m_staticMoving)
			{
				m_panStart = m_panEnd;
			}
			else
			{
				m_panStart += (m_panEnd - m_panStart) * m_dynamicDampingFactor; //  (_panEnd - _panStart).scale(_dynamicDampingFactor);
			}
		}
	}

	void trackball::CheckDistances()
	{
		if (!m_noZoom || !m_noPan)
		{
			if (glm::length2(m_pCam->m_eye)	 > m_maxDistance * m_maxDistance)
			{
				//  _camObject._pos.Normalize();
				//  _camObject._pos = Vector3.Multiply(_camObject._pos, _maxDistance);
				m_pCam->m_eye = glm::normalize(m_pCam->m_eye) * m_maxDistance;
			}
			if (glm::length2(m_eye) < m_minDistance * m_minDistance)
			{
				m_eye = glm::normalize(m_eye) * m_minDistance;
				m_pCam->m_eye = m_target + m_eye;
			}
		}
	}

	glm::vec3 trackball::GetMouseProjectionOnBall(int clientX, int clientY)
	{
		glm::vec3 mouseOnBall = glm::vec3(
			((float)clientX - (float)m_screen.z * 0.5f) / (float)(m_screen.z * 0.5f),
			((float)m_screen.w * 0.5f - (float)clientY) / (float)(m_screen.w * 0.5f),
			0.0f
		);
		double length = (double)glm::length(mouseOnBall);
		if (m_noRoll)
		{
			if (length < SQRT1_2)
			{
				mouseOnBall.z = (float)sqrt(1.0 - length * length);
			}
			else
			{
				mouseOnBall.z = (float)(0.5 / length);
			}
		}
		else if (length > 1.0)
		{
			mouseOnBall = glm::normalize(mouseOnBall);
		}
		else
		{
			mouseOnBall.z = (float)sqrt(1.0 - length * length);
		}
		m_eye = m_target - m_pCam->m_eye;
		glm::vec3 upClone = m_pCam->m_up;
		upClone = glm::normalize(upClone);
		glm::vec3 projection = upClone * mouseOnBall.y;
		glm::vec3 cross = glm::normalize(glm::cross(m_pCam->m_up, m_eye));
		cross *= mouseOnBall.x;
		projection += cross;
		glm::vec3 eyeClone = glm::normalize(m_eye);
		projection += eyeClone * mouseOnBall.z;
		return projection;
	}

	void trackball::MouseDown(int button, int action, int mods, int xpos, int ypos) {
		if (!m_enabled) { return; }
		if (m_state == TCB_STATE::NONE)
		{
			if (button == GLFW_MOUSE_BUTTON_RIGHT)
			{
				m_state = TCB_STATE::PAN;
			}
			else
			{
				m_state = TCB_STATE::ROTATE;
			}
			//   _state = e.Button;//  event.button;
		}
		if (m_state == TCB_STATE::ROTATE && !m_noRotate)
		{
			m_rotStart = GetMouseProjectionOnBall(xpos, ypos);
			m_rotEnd = m_rotStart;
		}
		else if (m_state == TCB_STATE::ZOOM && !m_noZoom)
		{
			m_zoomStart = GetMouseOnScreen(xpos, ypos);
			m_zoomEnd = m_zoomStart;
		}
		else if (m_state == TCB_STATE::PAN && !m_noPan)
		{
			m_panStart = GetMouseOnScreen(xpos, ypos);
			m_panEnd = m_panStart;
		}
	}

	void trackball::KeyDown(int key) {

		if (!m_enabled) return;

		m_prevState = m_state;

		if (m_state != TCB_STATE::NONE)
		{

			return;

		}
		else if (key == GLFW_KEY_A /* event.keyCode == keys[ STATE.ROTATE ]*/ && !m_noRotate)
		{

			m_state = TCB_STATE::ROTATE;

		}
		else if (key == GLFW_KEY_S /* event.keyCode == keys[ STATE.ZOOM ]*/ && !m_noZoom)
		{

			m_state = TCB_STATE::ZOOM;

		}
		else if (key == GLFW_KEY_D /* event.keyCode == keys[ STATE.PAN ]*/ && !m_noPan)
		{

			m_state = TCB_STATE::PAN;

		}
	}

	void trackball::MouseWheel(double xoffset, double yoffset) {

		if (!m_enabled) { return; }


		float delta = 0.0f;



		if (yoffset != 0.0)
		{ // Firefox

			delta = (float)yoffset / 3.0f;

		}

		m_zoomStart.y += delta * 0.05f;
	}

	void trackball::MouseMove(int xpos, int ypos) {
		if (!m_enabled) { return; }

		if (m_state == TCB_STATE::ROTATE && !m_noRotate)
		{
			m_rotEnd = GetMouseProjectionOnBall(xpos, ypos);
		}
		else if (m_state == TCB_STATE::ZOOM && !m_noZoom)
		{
			m_zoomEnd = GetMouseOnScreen(xpos, ypos);
		}
		else if (m_state == TCB_STATE::PAN && !m_noPan)
		{
			m_panEnd = GetMouseOnScreen(xpos, ypos);
		}
	}
}
