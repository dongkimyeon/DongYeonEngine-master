#include "GameObject.h"
#include "Input.h"
#include "Time.h"

GameObject::GameObject()
	: mX(0)
	, mY(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	const int speed = 100.0f;
	if (Input::GetKey(eKeyCode::A))
	{
		mX -= speed * Time::DeltaTime();
	}

	if (Input::GetKey(eKeyCode::D))
	{
		mX += speed * Time::DeltaTime();
	}

	if (Input::GetKey(eKeyCode::W))
	{
		mY -= speed * Time::DeltaTime();
	}

	if (Input::GetKey(eKeyCode::S))
	{
		mY += speed * Time::DeltaTime();
	}

}

void GameObject::LateUpdate()
{

}

void GameObject::Render(HDC hdc)
{
	//�Ķ� �귯�� ����
	HBRUSH randomBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));

	// �Ķ� �귯�� DC�� ���� �׸��� ��� �귯�� ��ȯ�� ��ȯ
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randomBrush);

	
	WCHAR Text[100];
	wsprintf(Text, L"X : %d Y : %d", (int)Input::GetMousePosition().x, (int)Input::GetMousePosition().y);
	TextOut(hdc, Input::GetMousePosition().x + 10, Input::GetMousePosition().y, Text, lstrlen(Text));
	
	
	//Ellipse(hdc, Input::GetMousePosition().x , Input::GetMousePosition().y, 100 + Input::GetMousePosition().y, 100 + Input::GetMousePosition().y);

	SelectObject(hdc, oldBrush);
	DeleteObject(randomBrush);
	
}
