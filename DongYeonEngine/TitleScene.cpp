#include "TitleScene.h"
#include "GameObject.h"
#include "SceneManager.h"

TitleScene::TitleScene()
    : mBackgroundImage(nullptr)
    , mGdiplusToken(0)
{
    // GDI+ 초기화
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&mGdiplusToken, &gdiplusStartupInput, nullptr);
}

TitleScene::~TitleScene()
{
    if (mBackgroundImage != nullptr)
    {
        delete mBackgroundImage; // 이미지 객체 해제
        mBackgroundImage = nullptr;
    }

    // GDI+ 종료
    if (mGdiplusToken != 0)
    {
        Gdiplus::GdiplusShutdown(mGdiplusToken);
        mGdiplusToken = 0;
    }
}

void TitleScene::Initialize()
{

    mBackgroundImage = new Gdiplus::Image(L"resources/maintitle.png");
    if (mBackgroundImage->GetLastStatus() != Gdiplus::Ok) //로드됐는지 안됐는지 확인
    {
        MessageBox(NULL, L"Failed to load background.png", L"Error", MB_OK);

        delete mBackgroundImage;
        mBackgroundImage = nullptr;
    }

}

void TitleScene::Update()
{
    Scene::Update();

    // 스페이스 키로 PlayScene 전환
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        SceneManager::LoadScene(L"PlayScene");
    }
}

void TitleScene::LateUpdate()
{
    Scene::LateUpdate();
}

void TitleScene::Render(HDC hdc)
{
    Scene::Render(hdc);
    Gdiplus::Graphics graphics(hdc);

    // 이미지 원본 크기
    float imgWidth = static_cast<float>(mBackgroundImage->GetWidth());
    float imgHeight = static_cast<float>(mBackgroundImage->GetHeight());

    // 스케일링 비율 계산 (창에 맞게 축소)
    float scaleX = static_cast<float>(1280 / imgWidth);
    float scaleY = static_cast<float>(720 / imgHeight);
    float scale = min(scaleX, scaleY); // 더 작은 비율 선택 (창 안에 들어가게)

    // 이미지가 창보다 작을 경우 원본 크기 유지
    if (scale > 1.0f) scale = 1.0f;

    // 새 이미지 크기 계산
    int destWidth = static_cast<int>(imgWidth * scale);
    int destHeight = static_cast<int>(imgHeight * scale);

    // 중앙 정렬을 위한 오프셋
    int destX = (1280 - destWidth) / 2;
    int destY = (720 - destHeight) / 2;

    // 이미지 그리기
    graphics.DrawImage(mBackgroundImage, 0, 0, destWidth, destHeight);

}