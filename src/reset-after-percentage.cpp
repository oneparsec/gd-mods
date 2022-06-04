#include <Windows.h>
#include <iostream>
#include <MinHook.h>
#include <gd.h>
#include <cocos2d.h>
#include <extensions2.h>

using namespace cocos2d;
using namespace MegaHackExt;

// creating gui elements
// yeah i need them to be global
Window *window = Window::Create("Reset after %");
CheckBox *checkbox = CheckBox::Create("Enabled");
Spinner *spinner = Spinner::Create(nullptr, "%");


namespace PlayLayer {
    inline void(__thiscall* update)(gd::PlayLayer* self, float delta);
	void __fastcall hkUpdate(gd::PlayLayer* self, void*, float delta);

	inline int(__thiscall* resetLevel)(void* self);
	int __fastcall hkReset(gd::PlayLayer* self);

    void mem_init();
}


void __fastcall PlayLayer::hkUpdate(gd::PlayLayer* self, void* edx, float delta) {

    if (spinner->get() > (double)100)
    {
        spinner->set(100);
    }

    if (checkbox->get())
    {
        if (round(self->m_levelLength / 100 * spinner->get()) <= round(self->m_pPlayer1->getPositionX()))
        {
            resetLevel(self);
        }
    }
	return update(self, delta);
}

int __fastcall PlayLayer::hkReset(gd::PlayLayer* self) {

    return resetLevel(self);
}



void PlayLayer::mem_init() {
	size_t base = (size_t)GetModuleHandle(0);
	MH_CreateHook(
		(PVOID)(base + 0x2029C0),
		PlayLayer::hkUpdate,
		(LPVOID*)&PlayLayer::update);
	MH_CreateHook(
		(PVOID)(base + 0x20BF00),
		PlayLayer::hkReset,
		(LPVOID*)&PlayLayer::resetLevel);
}

DWORD WINAPI MainThread(void* hModule) {
    MH_Initialize();

    window->add(HorizontalLayout::Create(spinner, checkbox));
    Client::commit(window);

    PlayLayer::mem_init();

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}


BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, MainThread, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}