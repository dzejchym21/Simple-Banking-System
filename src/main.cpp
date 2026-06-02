#include <iostream>
#include "Bank.h"
#include <GLFW/glfw3.h>
#include <string>
#include <cstring>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main() {
    if (!glfwInit()) return -1;

    Bank bank;
    static std::string activeAccountId = "";
    static float amountInput = 0.0f;
    static std::string statusMessage = "";
    static ImVec4 statusColor(1.0f, 1.0f, 1.0f, 1.0f);

    static bool openDepositTrigger = false;
    static bool openWithdrawTrigger = false;

    GLFWwindow* window = glfwCreateWindow(600, 600, "Simple Banking System", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int window_w, window_h;
        glfwGetFramebufferSize(window, &window_w, &window_h);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)window_w, (float)window_h));

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
                                 ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Main Banking Panel", nullptr, flags);

        ImGui::TextColored(ImVec4(0.2f, 0.7f, 1.0f, 1.0f), "SIMPLE BANKING SYSTEM");
        ImGui::Text("Banking Management Panel");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Create New Account:");
        static char name[64] = "";
        ImGui::InputText("Owner name", name, IM_ARRAYSIZE(name));

        if (ImGui::Button("Create", ImVec2(120, 30))) {
            if (std::strlen(name) > 0) {
                bank.createAccount(name, 0);
                name[0] = '\0';
            }
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Registered Accounts: (%d)", (int)bank.getAccounts().size());
        ImGui::BeginChild("ListaKontRegion", ImVec2(0, 0), true);

        for (const auto& [key, account] : bank.getAccounts()) {
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);

            std::string cardName = "Card_" + key;
            ImGui::BeginChild(cardName.c_str(), ImVec2(0, 65), true);

            ImGui::Text("Number: %s | Owner: %s", key.c_str(), account.getOwnerName().c_str());
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Balance: %.2f PLN", account.getBalance());

            ImGui::SameLine(ImGui::GetWindowWidth() - 160);
            if (ImGui::Button(("Deposit##" + cardName).c_str(), ImVec2(70, 25))) {
                activeAccountId = key;
                amountInput = 0.0f;
                statusMessage = "";
                openDepositTrigger = true;
            }

            ImGui::SameLine(ImGui::GetWindowWidth() - 80);
            if (ImGui::Button(("Withdraw##" + cardName).c_str(), ImVec2(70, 25))) {
                activeAccountId = key;
                amountInput = 0.0f;
                statusMessage = "";
                openWithdrawTrigger = true;
            }

            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::Spacing();
        }

        ImGui::EndChild();

        if (openDepositTrigger) {
            ImGui::OpenPopup("Deposit Funds");
            openDepositTrigger = false;
        }
        if (openWithdrawTrigger) {
            ImGui::OpenPopup("Withdraw Funds");
            openWithdrawTrigger = false;
        }

        if (ImGui::BeginPopupModal("Deposit Funds", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Account Target: %s", activeAccountId.c_str());
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::InputFloat("Amount (PLN)", &amountInput, 10.0f, 100.0f, "%.2f");
            ImGui::Spacing();

            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (amountInput > 0) {
                    bank.depositTo(activeAccountId, amountInput);
                    statusMessage = "Successfully deposited!";
                    statusColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
                } else {
                    statusMessage = "Error: Invalid amount!";
                    statusColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Close", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }

            if (!statusMessage.empty()) {
                ImGui::Spacing();
                ImGui::TextColored(statusColor, "%s", statusMessage.c_str());
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopupModal("Withdraw Funds", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Account Target: %s", activeAccountId.c_str());
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::InputFloat("Amount (PLN)", &amountInput, 10.0f, 100.0f, "%.2f");
            ImGui::Spacing();

            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (amountInput <= 0) {
                    statusMessage = "Error: Invalid amount!";
                    statusColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                } else {
                    bool success = bank.withdrawFrom(activeAccountId, amountInput);
                    if (success) {
                        statusMessage = "Successfully withdrawn!";
                        statusColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
                    } else {
                        statusMessage = "Error: Insufficient funds!";
                        statusColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                    }
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Close", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }

            if (!statusMessage.empty()) {
                ImGui::Spacing();
                ImGui::TextColored(statusColor, "%s", statusMessage.c_str());
            }
            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}