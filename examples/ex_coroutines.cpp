#include <Mahi/Gui.hpp>

using namespace mahi::gui;
using namespace mahi::util;

class CoroDemo : public Application {
public:
    CoroDemo() : Application(250,250, "Coroutine Demo", false) { 
        background_color = Grays::Black;
        ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_ViewportsEnable;
    }

    void update() {
        // controls
        ImGui::SetNextWindowPos({10,10});
        ImGui::Begin("Coro Demo", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        if (ImGui::Button("Move X")) 
            startCoroutine(move(0));
        ImGui::SameLine();
        if (ImGui::Button("Move Y"))
            startCoroutine(move(1));
        ImGui::SameLine();
        if (ImGui::Button("Blink"))
            startCoroutine(blink());
        ImGui::SameLine();
        if (ImGui::Button("Go Crazy"))
            startCoroutine(goCrazy());
        ImGui::Text("Coroutine Count: %d", coroutineCount());
        ImGui::End();
        // draw
        ImGui::GetBackgroundDrawList()->AddCircleFilled(pos, 50, col, 100);
    }

    Enumerator move(int axis) {
        float t = 0;
        while (t < 5) {
            pos[axis] = 125 + 50 * std::sin(2*PI*t + HALFPI * axis);
            t += ImGui::GetIO().DeltaTime;
            co_yield nullptr;
        }
    }

    Enumerator blink() {
        auto col1 = ImGui::GetColorU32(Grays::Black);
        auto col2 = ImGui::GetColorU32(Greens::Chartreuse);
        for (int i = 0; i < 20; ++i) {
            col = col1;
            co_yield new WaitForSeconds(0.1f);
            col = col2;
            co_yield new WaitForSeconds(0.15f);
        }
    }

    Enumerator goCrazy() {
        startCoroutine(blink());
        startCoroutine(move(0));
        co_yield startCoroutine(move(1));
    }

    ImVec2 pos = {125,175};
    ImU32 col = ImGui::GetColorU32(Greens::Chartreuse);
};

int main(int argc, char const *argv[])
{
    CoroDemo demo;
    demo.run();
    return 0;
}
