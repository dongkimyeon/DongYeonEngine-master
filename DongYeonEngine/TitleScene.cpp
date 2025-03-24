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
    mLogoImage = new Gdiplus::Image(L"resources/TitleLogo.png");

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

    // 백그라운드 이미지 그리기
    float bgImgWidth = static_cast<float>(mBackgroundImage->GetWidth());
    float bgImgHeight = static_cast<float>(mBackgroundImage->GetHeight());

    // 스케일링 비율 계산 (창에 맞게 축소)
    float scaleX = static_cast<float>(1280 / bgImgWidth);
    float scaleY = static_cast<float>(720 / bgImgHeight);
    float backGroundScale = min(scaleX, scaleY); // 더 작은 비율 선택 (창 안에 들어가게)

    // 이미지가 창보다 작을 경우 원본 크기 유지
    if (backGroundScale > 1.0f) backGroundScale = 1.0f;

    // 새 이미지 크기 계산
    int destWidth = static_cast<int>(bgImgWidth * backGroundScale);
    int destHeight = static_cast<int>(bgImgHeight * backGroundScale);

    // 중앙 정렬을 위한 오프셋
    int destX = (1280 - destWidth) / 2;
    int destY = (720 - destHeight) / 2;

    // 백그라운드 이미지 그리기
    graphics.DrawImage(mBackgroundImage, destX, destY, destWidth, destHeight);

    // 로고 이미지 그리기
    float logoWidth = static_cast<float>(mLogoImage->GetWidth());
    float logoHeight = static_cast<float>(mLogoImage->GetHeight());

    // 로고 이미지를 중앙에 배치 (원하는 위치로 조정 가능)
    int logoX = (1280 - static_cast<int>(logoWidth)) / 2;  // 로고를 수평 중앙에
    int logoY = ((720 - static_cast<int>(logoHeight)) / 2 ) - 100;  // 로고를 수직 중앙에

    // 로고 이미지 그리기 (원본 크기 유지)
    graphics.DrawImage(mLogoImage, logoX, logoY + 100, static_cast<int>(logoWidth), static_cast<int>(logoHeight));

    TextOut(hdc, 1280 / 2, 200, L"스페이스바를 눌러 다음 화면으로 넘어가세요", 23);

}