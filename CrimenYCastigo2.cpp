#include "pch.h"
#include "FrmMenu.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew CrimenYCastigo2::FrmMenu());
    return 0;

}