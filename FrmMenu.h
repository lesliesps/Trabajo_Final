#pragma once
#include "FrmJuego.h"
#include "FrmCreditos.h"
namespace CrimenYCastigo2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FrmMenu
	/// </summary>
	public ref class FrmMenu : public System::Windows::Forms::Form
	{
	public:
		FrmMenu(void)
		{
			InitializeComponent();

			musicaMenu = gcnew System::Media::SoundPlayer("Sonidos\\MusicaMenu.wav");
			musicaMenu->PlayLooping();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FrmMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblTituloJuego;
	protected:

	private: System::Windows::Forms::Button^ btnJugar;
	private: System::Windows::Forms::Button^ btnCreditos;
	private: System::Windows::Forms::Button^ btnSalir;
	private: System::Windows::Forms::Panel^ pnlFondoMenu;


	private: System::Windows::Forms::Panel^ pnlAnimacionMenu;
	private: System::Windows::Forms::Panel^ pnlScanline;
	private: System::Windows::Forms::Timer^ timerScanline;
	private: System::ComponentModel::IContainer^ components;
	private: System::Media::SoundPlayer^ musicaMenu;


	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmMenu::typeid));
			this->lblTituloJuego = (gcnew System::Windows::Forms::Label());
			this->btnJugar = (gcnew System::Windows::Forms::Button());
			this->btnCreditos = (gcnew System::Windows::Forms::Button());
			this->btnSalir = (gcnew System::Windows::Forms::Button());
			this->pnlFondoMenu = (gcnew System::Windows::Forms::Panel());
			this->pnlAnimacionMenu = (gcnew System::Windows::Forms::Panel());
			this->pnlScanline = (gcnew System::Windows::Forms::Panel());
			this->timerScanline = (gcnew System::Windows::Forms::Timer(this->components));
			this->pnlFondoMenu->SuspendLayout();
			this->pnlAnimacionMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// lblTituloJuego
			// 
			this->lblTituloJuego->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblTituloJuego->BackColor = System::Drawing::Color::Transparent;
			this->lblTituloJuego->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblTituloJuego->Font = (gcnew System::Drawing::Font(L"Stencil", 72, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTituloJuego->ForeColor = System::Drawing::Color::MintCream;
			this->lblTituloJuego->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lblTituloJuego.Image")));
			this->lblTituloJuego->Location = System::Drawing::Point(380, 157);
			this->lblTituloJuego->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblTituloJuego->Name = L"lblTituloJuego";
			this->lblTituloJuego->Size = System::Drawing::Size(684, 94);
			this->lblTituloJuego->TabIndex = 1;
			this->lblTituloJuego->Click += gcnew System::EventHandler(this, &FrmMenu::lblTituloJuego_Click);
			// 
			// btnJugar
			// 
			this->btnJugar->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->btnJugar->BackColor = System::Drawing::Color::Transparent;
			this->btnJugar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnJugar.BackgroundImage")));
			this->btnJugar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btnJugar->CausesValidation = false;
			this->btnJugar->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnJugar->FlatAppearance->BorderSize = 0;
			this->btnJugar->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->btnJugar->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnJugar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnJugar->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 11, System::Drawing::FontStyle::Bold));
			this->btnJugar->ForeColor = System::Drawing::Color::DarkGoldenrod;
			this->btnJugar->Location = System::Drawing::Point(546, 324);
			this->btnJugar->Margin = System::Windows::Forms::Padding(2);
			this->btnJugar->Name = L"btnJugar";
			this->btnJugar->Size = System::Drawing::Size(350, 115);
			this->btnJugar->TabIndex = 2;
			this->btnJugar->Text = L"PLAYGAME";
			this->btnJugar->UseVisualStyleBackColor = false;
			this->btnJugar->Click += gcnew System::EventHandler(this, &FrmMenu::btnJugar_Click);
			// 
			// btnCreditos
			// 
			this->btnCreditos->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->btnCreditos->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnCreditos.BackgroundImage")));
			this->btnCreditos->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btnCreditos->CausesValidation = false;
			this->btnCreditos->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnCreditos->FlatAppearance->BorderSize = 0;
			this->btnCreditos->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->btnCreditos->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnCreditos->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnCreditos->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 11, System::Drawing::FontStyle::Bold));
			this->btnCreditos->ForeColor = System::Drawing::Color::DarkGoldenrod;
			this->btnCreditos->Location = System::Drawing::Point(546, 413);
			this->btnCreditos->Margin = System::Windows::Forms::Padding(2);
			this->btnCreditos->Name = L"btnCreditos";
			this->btnCreditos->Size = System::Drawing::Size(350, 115);
			this->btnCreditos->TabIndex = 3;
			this->btnCreditos->Text = L"CREDITOS";
			this->btnCreditos->UseVisualStyleBackColor = true;
			this->btnCreditos->Click += gcnew System::EventHandler(this, &FrmMenu::btnCreditos_Click);
			// 
			// btnSalir
			// 
			this->btnSalir->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->btnSalir->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSalir.BackgroundImage")));
			this->btnSalir->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btnSalir->CausesValidation = false;
			this->btnSalir->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnSalir->FlatAppearance->BorderSize = 0;
			this->btnSalir->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->btnSalir->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnSalir->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSalir->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 11, System::Drawing::FontStyle::Bold));
			this->btnSalir->ForeColor = System::Drawing::Color::DarkGoldenrod;
			this->btnSalir->Location = System::Drawing::Point(546, 502);
			this->btnSalir->Margin = System::Windows::Forms::Padding(2);
			this->btnSalir->Name = L"btnSalir";
			this->btnSalir->Size = System::Drawing::Size(350, 115);
			this->btnSalir->TabIndex = 4;
			this->btnSalir->Text = L"SALIR";
			this->btnSalir->UseVisualStyleBackColor = true;
			this->btnSalir->Click += gcnew System::EventHandler(this, &FrmMenu::btnSalir_Click);
			// 
			// pnlFondoMenu
			// 
			this->pnlFondoMenu->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pnlFondoMenu.BackgroundImage")));
			this->pnlFondoMenu->Controls->Add(this->pnlAnimacionMenu);
			this->pnlFondoMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlFondoMenu->Location = System::Drawing::Point(0, 0);
			this->pnlFondoMenu->Margin = System::Windows::Forms::Padding(2);
			this->pnlFondoMenu->Name = L"pnlFondoMenu";
			this->pnlFondoMenu->Size = System::Drawing::Size(1426, 839);
			this->pnlFondoMenu->TabIndex = 5;
			// 
			// pnlAnimacionMenu
			// 
			this->pnlAnimacionMenu->BackColor = System::Drawing::Color::Transparent;
			this->pnlAnimacionMenu->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pnlAnimacionMenu.BackgroundImage")));
			this->pnlAnimacionMenu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pnlAnimacionMenu->Controls->Add(this->pnlScanline);
			this->pnlAnimacionMenu->Controls->Add(this->lblTituloJuego);
			this->pnlAnimacionMenu->Controls->Add(this->btnSalir);
			this->pnlAnimacionMenu->Controls->Add(this->btnJugar);
			this->pnlAnimacionMenu->Controls->Add(this->btnCreditos);
			this->pnlAnimacionMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlAnimacionMenu->Location = System::Drawing::Point(0, 0);
			this->pnlAnimacionMenu->Margin = System::Windows::Forms::Padding(2);
			this->pnlAnimacionMenu->Name = L"pnlAnimacionMenu";
			this->pnlAnimacionMenu->Size = System::Drawing::Size(1426, 839);
			this->pnlAnimacionMenu->TabIndex = 6;
			this->pnlAnimacionMenu->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FrmMenu::pnlAnimacionMenu_Paint);
			// 
			// pnlScanline
			// 
			this->pnlScanline->BackColor = System::Drawing::Color::Black;
			this->pnlScanline->Location = System::Drawing::Point(0, 0);
			this->pnlScanline->Name = L"pnlScanline";
			this->pnlScanline->Size = System::Drawing::Size(1424, 3);
			this->pnlScanline->TabIndex = 5;
			// 
			// timerScanline
			// 
			this->timerScanline->Enabled = true;
			this->timerScanline->Interval = 20;
			this->timerScanline->Tick += gcnew System::EventHandler(this, &FrmMenu::timerScanline_Tick);
			// 
			// FrmMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1426, 839);
			this->Controls->Add(this->pnlFondoMenu);
			this->Margin = System::Windows::Forms::Padding(2);
			this->MinimizeBox = false;
			this->Name = L"FrmMenu";
			this->Text = L"FrmMenu";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->pnlFondoMenu->ResumeLayout(false);
			this->pnlAnimacionMenu->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		private:System::Void btnJugar_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Hide();
			FrmJuego^ juego = gcnew FrmJuego();
			juego->ShowDialog();
			this->Close();
		}
	System::Void btnCreditos_Click(System::Object^ sender, System::EventArgs^ e)
		{
			FrmCreditos^ creditos = gcnew FrmCreditos();
			if (creditos->ShowDialog() == System::Windows::Forms::DialogResult::Abort)
				this->Close();
		}

		private: System::Void btnSalir_Click(System::Object^ sender, System::EventArgs^ e) {
		   this->Close();
		}
private: System::Void lblTituloJuego_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void timerScanline_Tick(System::Object^ sender, System::EventArgs^ e) {
	pnlScanline->BringToFront();
	pnlScanline->Width = pnlScanline->Parent->ClientSize.Width;
	pnlScanline->Top += 6;

	if (pnlScanline->Top >= pnlScanline->Parent->ClientSize.Height) {
		pnlScanline->Top = -pnlScanline->Height;
	}
}
private: System::Void pnlAnimacionMenu_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	System::Windows::Forms::Control^ fondo =
		safe_cast<System::Windows::Forms::Control^>(sender);

	System::Drawing::Pen^ linea = gcnew System::Drawing::Pen(
		System::Drawing::Color::FromArgb(60, 0, 0, 0));

	for (int y = 0; y < fondo->ClientSize.Height; y += 4) {
		e->Graphics->DrawLine(
			linea, 0, y, fondo->ClientSize.Width, y);
	}

	delete linea;
}
};
}
