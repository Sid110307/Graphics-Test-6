#include "include/shape.h"

static constexpr auto WIDTH = 1920, HEIGHT = 1080;
static constexpr auto TITLE = "Graphics Test 6";

HWND__* hwnd;
HINSTANCE__* hInstance;
ULONG_PTR gdiplusToken;
std::vector<std::shared_ptr<Shape>> shapes;

LRESULT CALLBACK WindowProc(HWND__* hwnd, const UINT message, const WPARAM wParam, const LPARAM lParam);

void AddShape(const std::shared_ptr<Shape>& shape) { shapes.push_back(shape); }
void ClearShapes() { shapes.clear(); }

void init(HINSTANCE__* hInstance)
{
	const Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "WindowClass";
	RegisterClass(&wc);

	hwnd = CreateWindow(wc.lpszClassName, TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
	                    nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
}

void cleanup(HINSTANCE__* hInstance)
{
	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ClearShapes();
	Gdiplus::GdiplusShutdown(gdiplusToken);
	DestroyWindow(hwnd);
	UnregisterClass("WindowClass", hInstance);
}

int WINAPI WinMain(HINSTANCE__* hInstance, HINSTANCE__*, LPSTR, int)
{
	init(hInstance);

	AddShape(std::make_shared<Shape>(
		ShapeType::Polygon,
		std::vector<Gdiplus::PointF>{
			{100, 100},
			{200, 100},
			{200, 200},
			{100, 200},
		},
		Gdiplus::Color(124, 252, 0, 255)
	));

	AddShape(std::make_shared<Shape>(
		ShapeType::Rectangle,
		std::vector<Gdiplus::PointF>{
			{300, 300},
			{400, 300},
			{400, 400},
			{300, 400},
		},
		Gdiplus::Color(255, 0, 0, 255)
	));

	AddShape(std::make_shared<Shape>(
		ShapeType::Circle,
		std::vector<Gdiplus::PointF>{
			{500, 500},
			{600, 600},
		},
		Gdiplus::Color(0, 42, 136, 255)
	));

	cleanup(hInstance);
	return EXIT_SUCCESS;
}

LRESULT CALLBACK WindowProc(HWND__* hwnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	PAINTSTRUCT ps;

	if (message == WM_PAINT)
	{
		HDC__* hdc = BeginPaint(hwnd, &ps);
		Gdiplus::Graphics graphics(hdc);

		graphics.Clear(Gdiplus::Color(255, 255, 255, 255));
		for (const auto& shape : shapes) shape->Draw(graphics);
		EndPaint(hwnd, &ps);

		return EXIT_SUCCESS;
	}
	if (message == WM_DESTROY)
	{
		PostQuitMessage(EXIT_SUCCESS);
		return EXIT_SUCCESS;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
