#include "TitleScene.h"
#include "GameObject.h"
#include "SceneManager.h"

extern const UINT width;
extern const UINT height;

TitleScene::TitleScene()
    : mBackgroundImage(nullptr)
    , mLogoImage(nullptr)
    , mGdiplusToken(0)
{
    // GDI+ �ʱ�ȭ
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&mGdiplusToken, &gdiplusStartupInput, nullptr);
}

TitleScene::~TitleScene()
{
    if (mBackgroundImage != nullptr)
    {
        delete mBackgroundImage; // �̹��� ��ü ����
        mBackgroundImage = nullptr;
    }
    if (mLogoImage != nullptr)
    {
        delete mLogoImage; // �̹��� ��ü ����
        mLogoImage = nullptr;
    }
    // GDI+ ����
    if (mGdiplusToken != 0)
    {
        Gdiplus::GdiplusShutdown(mGdiplusToken);
        mGdiplusToken = 0;
    }
}

void TitleScene::Initialize()
{
    //�̹��� �ε�
    mBackgroundImage = new Gdiplus::Image(L"resources/maintitle.png");
    mLogoImage = new Gdiplus::Image(L"resources/TitileLogo.png");

}

void TitleScene::Update()
{
    Scene::Update();

    // �����̽� Ű�� PlayScene ��ȯ
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

    // ��׶��� �̹��� �׸���
    float bgImgWidth = static_cast<float>(mBackgroundImage->GetWidth());
    float bgImgHeight = static_cast<float>(mBackgroundImage->GetHeight());

    // �����ϸ� ���� ��� (â�� �°� ���)
    float scaleX = static_cast<float>(width / bgImgWidth);
    float scaleY = static_cast<float>(height / bgImgHeight);
    float backGroundScale = min(scaleX, scaleY); // �� ���� ���� ���� (â �ȿ� ����)

    // �̹����� â���� ���� ��� ���� ũ�� ����
    if (backGroundScale > 1.0f) backGroundScale = 1.0f;

    // �� �̹��� ũ�� ���
    int destWidth = static_cast<int>(bgImgWidth * backGroundScale);
    int destHeight = static_cast<int>(bgImgHeight * backGroundScale);

    // �߾� ������ ���� ������
    int destX = (width - destWidth) / 2;
    int destY = (height - destHeight) / 2;

   
    
    // �ΰ� �̹��� �׸���
    float logoWidth = static_cast<float>(mLogoImage->GetWidth());
    float logoHeight = static_cast<float>(mLogoImage->GetHeight());

    // �ΰ� �̹����� ��׶���� ������ �����ϸ� ����
    float logoScaleX = static_cast<float>(width / logoWidth);
    float logoScaleY = static_cast<float>(height / logoHeight);
    float logoScale = min(logoScaleX, logoScaleY); // �� ���� ���� ���� (â �ȿ� ����)

    // �ΰ� �̹����� â���� ���� ��� ���� ũ�� ����
    if (logoScale > 1.0f) logoScale = 1.0f;

    // �� �ΰ� �̹��� ũ�� ���
    int logoDestWidth = static_cast<int>(logoWidth * logoScale);
    int logoDestHeight = static_cast<int>(logoHeight * logoScale);

    // �ΰ� �̹����� ȭ�� ���߾ӿ� ��ġ
    int logoX = (width - logoDestWidth) / 2;  // ���� �߾�
    int logoY = (height - logoDestHeight) / 2; // ���� �߾�

    // �̹��� ������
    graphics.DrawImage(mBackgroundImage, destX, destY, destWidth, destHeight);
    graphics.DrawImage(mLogoImage, logoX, logoY, logoDestWidth, logoDestHeight);

}