#pragma once

namespace CrimenYCastigo2
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class FrmCreditos : public System::Windows::Forms::Form
	{
	public:
		FrmCreditos(void)
		{
			InitializeComponent();
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		}

	protected:
		~FrmCreditos()
		{
			if (components)
				delete components;
		}

	private:
		System::Windows::Forms::Panel^ pnlCapa;
		System::Windows::Forms::Label^ lblTitulo;
		System::Windows::Forms::Label^ lblCreadoPor;
		System::Windows::Forms::Label^ lblNombre;
		System::Windows::Forms::Label^ lblHamp;
		System::Windows::Forms::Panel^ pnlLinea;
		System::Windows::Forms::Label^ lblTecnologia;
		System::Windows::Forms::Panel^ pnlTec1;
		System::Windows::Forms::Label^ lblTec1Titulo;
		System::Windows::Forms::Label^ lblTec1Texto;
		System::Windows::Forms::Panel^ pnlTec2;
		System::Windows::Forms::Label^ lblTec2Titulo;
		System::Windows::Forms::Label^ lblTec2Texto;
		System::Windows::Forms::Panel^ pnlTec3;
		System::Windows::Forms::Label^ lblTec3Titulo;
		System::Windows::Forms::Label^ lblTec3Texto;
		System::Windows::Forms::Panel^ pnlTec4;
		System::Windows::Forms::Label^ lblTec4Titulo;
		System::Windows::Forms::Label^ lblTec4Texto;
		System::Windows::Forms::Panel^ pnlTec5;
		System::Windows::Forms::Label^ lblTec5Titulo;
		System::Windows::Forms::Label^ lblTec5Texto;
		System::Windows::Forms::Panel^ pnlTec6;
		System::Windows::Forms::Label^ lblTec6Titulo;
		System::Windows::Forms::Label^ lblTec6Texto;



		System::Windows::Forms::Button^ btnVolver;
		System::Windows::Forms::Button^ btnSalir;
	private: System::Windows::Forms::Panel^ pnlScanline;
	private: System::Windows::Forms::Timer^ timerScanline;
		   System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmCreditos::typeid));
			this->pnlCapa = (gcnew System::Windows::Forms::Panel());
			this->pnlScanline = (gcnew System::Windows::Forms::Panel());
			this->btnSalir = (gcnew System::Windows::Forms::Button());
			this->btnVolver = (gcnew System::Windows::Forms::Button());
			this->pnlTec6 = (gcnew System::Windows::Forms::Panel());
			this->lblTec6Texto = (gcnew System::Windows::Forms::Label());
			this->lblTec6Titulo = (gcnew System::Windows::Forms::Label());
			this->pnlTec5 = (gcnew System::Windows::Forms::Panel());
			this->lblTec5Texto = (gcnew System::Windows::Forms::Label());
			this->lblTec5Titulo = (gcnew System::Windows::Forms::Label());
			this->pnlTec4 = (gcnew System::Windows::Forms::Panel());
			this->lblTec4Texto = (gcnew System::Windows::Forms::Label());
			this->lblTec4Titulo = (gcnew System::Windows::Forms::Label());
			this->pnlTec3 = (gcnew System::Windows::Forms::Panel());
			this->lblTec3Texto = (gcnew System::Windows::Forms::Label());
			this->lblTec3Titulo = (gcnew System::Windows::Forms::Label());
			this->pnlTec2 = (gcnew System::Windows::Forms::Panel());
			this->lblTec2Texto = (gcnew System::Windows::Forms::Label());
			this->lblTec2Titulo = (gcnew System::Windows::Forms::Label());
			this->pnlTec1 = (gcnew System::Windows::Forms::Panel());
			this->lblTec1Texto = (gcnew System::Windows::Forms::Label());
			this->lblTec1Titulo = (gcnew System::Windows::Forms::Label());
			this->lblTecnologia = (gcnew System::Windows::Forms::Label());
			this->pnlLinea = (gcnew System::Windows::Forms::Panel());
			this->lblHamp = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->lblCreadoPor = (gcnew System::Windows::Forms::Label());
			this->lblTitulo = (gcnew System::Windows::Forms::Label());
			this->timerScanline = (gcnew System::Windows::Forms::Timer(this->components));
			this->pnlCapa->SuspendLayout();
			this->pnlTec6->SuspendLayout();
			this->pnlTec5->SuspendLayout();
			this->pnlTec4->SuspendLayout();
			this->pnlTec3->SuspendLayout();
			this->pnlTec2->SuspendLayout();
			this->pnlTec1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlCapa
			// 
			this->pnlCapa->BackColor = System::Drawing::Color::Transparent;
			this->pnlCapa->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pnlCapa.BackgroundImage")));
			this->pnlCapa->Controls->Add(this->pnlScanline);
			this->pnlCapa->Controls->Add(this->btnSalir);
			this->pnlCapa->Controls->Add(this->btnVolver);
			this->pnlCapa->Controls->Add(this->pnlTec6);
			this->pnlCapa->Controls->Add(this->pnlTec5);
			this->pnlCapa->Controls->Add(this->pnlTec4);
			this->pnlCapa->Controls->Add(this->pnlTec3);
			this->pnlCapa->Controls->Add(this->pnlTec2);
			this->pnlCapa->Controls->Add(this->pnlTec1);
			this->pnlCapa->Controls->Add(this->lblTecnologia);
			this->pnlCapa->Controls->Add(this->pnlLinea);
			this->pnlCapa->Controls->Add(this->lblHamp);
			this->pnlCapa->Controls->Add(this->lblNombre);
			this->pnlCapa->Controls->Add(this->lblCreadoPor);
			this->pnlCapa->Controls->Add(this->lblTitulo);
			this->pnlCapa->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlCapa->Location = System::Drawing::Point(0, 0);
			this->pnlCapa->Name = L"pnlCapa";
			this->pnlCapa->Size = System::Drawing::Size(1000, 750);
			this->pnlCapa->TabIndex = 0;
			this->pnlCapa->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FrmCreditos::pnlCapa_Paint);
			// 
			// pnlScanline
			// 
			this->pnlScanline->BackColor = System::Drawing::Color::Black;
			this->pnlScanline->Location = System::Drawing::Point(0, 0);
			this->pnlScanline->Name = L"pnlScanline";
			this->pnlScanline->Size = System::Drawing::Size(1010, 3);
			this->pnlScanline->TabIndex = 14;
			// 
			// btnSalir
			// 
			this->btnSalir->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(48)),
				static_cast<System::Int32>(static_cast<System::Byte>(24)));
			this->btnSalir->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnSalir->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
			this->btnSalir->FlatAppearance->BorderSize = 2;
			this->btnSalir->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSalir->Font = (gcnew System::Drawing::Font(L"Georgia", 12, System::Drawing::FontStyle::Bold));
			this->btnSalir->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnSalir->Location = System::Drawing::Point(884, 18);
			this->btnSalir->Name = L"btnSalir";
			this->btnSalir->Size = System::Drawing::Size(96, 38);
			this->btnSalir->TabIndex = 13;
			this->btnSalir->Text = L"Salir";
			this->btnSalir->UseVisualStyleBackColor = false;
			this->btnSalir->Click += gcnew System::EventHandler(this, &FrmCreditos::btnSalir_Click);
			// 
			// btnVolver
			// 
			this->btnVolver->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(48)),
				static_cast<System::Int32>(static_cast<System::Byte>(24)));
			this->btnVolver->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnVolver->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)),
				static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(70)));
			this->btnVolver->FlatAppearance->BorderSize = 2;
			this->btnVolver->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnVolver->Font = (gcnew System::Drawing::Font(L"Georgia", 15, System::Drawing::FontStyle::Bold));
			this->btnVolver->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnVolver->Location = System::Drawing::Point(380, 686);
			this->btnVolver->Name = L"btnVolver";
			this->btnVolver->Size = System::Drawing::Size(240, 54);
			this->btnVolver->TabIndex = 12;
			this->btnVolver->Text = L"Volver";
			this->btnVolver->UseVisualStyleBackColor = false;
			this->btnVolver->Click += gcnew System::EventHandler(this, &FrmCreditos::btnVolver_Click);
			// 
			// pnlTec6
			// 
			this->pnlTec6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->pnlTec6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlTec6->Controls->Add(this->lblTec6Texto);
			this->pnlTec6->Controls->Add(this->lblTec6Titulo);
			this->pnlTec6->Location = System::Drawing::Point(675, 498);
			this->pnlTec6->Name = L"pnlTec6";
			this->pnlTec6->Size = System::Drawing::Size(280, 120);
			this->pnlTec6->TabIndex = 11;
			// 
			// lblTec6Texto
			// 
			this->lblTec6Texto->Font = (gcnew System::Drawing::Font(L"Georgia", 12));
			this->lblTec6Texto->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblTec6Texto->Location = System::Drawing::Point(10, 46);
			this->lblTec6Texto->Name = L"lblTec6Texto";
			this->lblTec6Texto->Size = System::Drawing::Size(258, 66);
			this->lblTec6Texto->TabIndex = 1;
			this->lblTec6Texto->Text = L"Herramienta de IA utilizada para generar los sprites y el storyboard.";
			// 
			// lblTec6Titulo
			// 
			this->lblTec6Titulo->Font = (gcnew System::Drawing::Font(L"Georgia", 16, System::Drawing::FontStyle::Bold));
			this->lblTec6Titulo->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->lblTec6Titulo->Location = System::Drawing::Point(10, 10);
			this->lblTec6Titulo->Name = L"lblTec6Titulo";
			this->lblTec6Titulo->Size = System::Drawing::Size(258, 32);
			this->lblTec6Titulo->TabIndex = 0;
			this->lblTec6Titulo->Text = L"ChatGTP";
			// 
			// pnlTec5
			// 
			this->pnlTec5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->pnlTec5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlTec5->Controls->Add(this->lblTec5Texto);
			this->pnlTec5->Controls->Add(this->lblTec5Titulo);
			this->pnlTec5->Location = System::Drawing::Point(355, 498);
			this->pnlTec5->Name = L"pnlTec5";
			this->pnlTec5->Size = System::Drawing::Size(280, 120);
			this->pnlTec5->TabIndex = 10;
			// 
			// lblTec5Texto
			// 
			this->lblTec5Texto->Font = (gcnew System::Drawing::Font(L"Georgia", 12));
			this->lblTec5Texto->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblTec5Texto->Location = System::Drawing::Point(10, 46);
			this->lblTec5Texto->Name = L"lblTec5Texto";
			this->lblTec5Texto->Size = System::Drawing::Size(258, 66);
			this->lblTec5Texto->TabIndex = 1;
			this->lblTec5Texto->Text = L"Posiciones de los objetos, historia y conocimiento de Merlín.";
			// 
			// lblTec5Titulo
			// 
			this->lblTec5Titulo->Font = (gcnew System::Drawing::Font(L"Georgia", 16, System::Drawing::FontStyle::Bold));
			this->lblTec5Titulo->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lblTec5Titulo->Location = System::Drawing::Point(10, 10);
			this->lblTec5Titulo->Name = L"lblTec5Titulo";
			this->lblTec5Titulo->Size = System::Drawing::Size(258, 32);
			this->lblTec5Titulo->TabIndex = 0;
			this->lblTec5Titulo->Text = L"Archivos de texto";
			// 
			// pnlTec4
			// 
			this->pnlTec4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->pnlTec4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlTec4->Controls->Add(this->lblTec4Texto);
			this->pnlTec4->Controls->Add(this->lblTec4Titulo);
			this->pnlTec4->Location = System::Drawing::Point(35, 498);
			this->pnlTec4->Name = L"pnlTec4";
			this->pnlTec4->Size = System::Drawing::Size(280, 120);
			this->pnlTec4->TabIndex = 9;
			// 
			// lblTec4Texto
			// 
			this->lblTec4Texto->Font = (gcnew System::Drawing::Font(L"Georgia", 12));
			this->lblTec4Texto->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblTec4Texto->Location = System::Drawing::Point(10, 46);
			this->lblTec4Texto->Name = L"lblTec4Texto";
			this->lblTec4Texto->Size = System::Drawing::Size(258, 66);
			this->lblTec4Texto->TabIndex = 1;
			this->lblTec4Texto->Text = L"Reconocimiento de tu voz y respuestas con su base de conocimiento.";
			// 
			// lblTec4Titulo
			// 
			this->lblTec4Titulo->Font = (gcnew System::Drawing::Font(L"Georgia", 16, System::Drawing::FontStyle::Bold));
			this->lblTec4Titulo->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lblTec4Titulo->Location = System::Drawing::Point(10, 10);
			this->lblTec4Titulo->Name = L"lblTec4Titulo";
			this->lblTec4Titulo->Size = System::Drawing::Size(258, 32);
			this->lblTec4Titulo->TabIndex = 0;
			this->lblTec4Titulo->Text = L"IA";
			// 
			// pnlTec3
			// 
			this->pnlTec3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->pnlTec3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlTec3->Controls->Add(this->lblTec3Texto);
			this->pnlTec3->Controls->Add(this->lblTec3Titulo);
			this->pnlTec3->Location = System::Drawing::Point(675, 358);
			this->pnlTec3->Name = L"pnlTec3";
			this->pnlTec3->Size = System::Drawing::Size(280, 120);
			this->pnlTec3->TabIndex = 8;
			// 
			// lblTec3Texto
			// 
			this->lblTec3Texto->Font = (gcnew System::Drawing::Font(L"Georgia", 12));
			this->lblTec3Texto->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblTec3Texto->Location = System::Drawing::Point(10, 46);
			this->lblTec3Texto->Name = L"lblTec3Texto";
			this->lblTec3Texto->Size = System::Drawing::Size(258, 66);
			this->lblTec3Texto->TabIndex = 1;
			this->lblTec3Texto->Text = L"Programación orientada a objetos: clases, herencia y polimorfismo.";
			// 
			// lblTec3Titulo
			// 
			this->lblTec3Titulo->Font = (gcnew System::Drawing::Font(L"Georgia", 16, System::Drawing::FontStyle::Bold));
			this->lblTec3Titulo->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lblTec3Titulo->Location = System::Drawing::Point(10, 10);
			this->lblTec3Titulo->Name = L"lblTec3Titulo";
			this->lblTec3Titulo->Size = System::Drawing::Size(258, 32);
			this->lblTec3Titulo->TabIndex = 0;
			this->lblTec3Titulo->Text = L"POO";
			// 
			// pnlTec2
			// 
			this->pnlTec2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->pnlTec2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlTec2->Controls->Add(this->lblTec2Texto);
			this->pnlTec2->Controls->Add(this->lblTec2Titulo);
			this->pnlTec2->Location = System::Drawing::Point(355, 358);
			this->pnlTec2->Name = L"pnlTec2";
			this->pnlTec2->Size = System::Drawing::Size(280, 120);
			this->pnlTec2->TabIndex = 7;
			// 
			// lblTec2Texto
			// 
			this->lblTec2Texto->Font = (gcnew System::Drawing::Font(L"Georgia", 12));
			this->lblTec2Texto->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblTec2Texto->Location = System::Drawing::Point(10, 46);
			this->lblTec2Texto->Name = L"lblTec2Texto";
			this->lblTec2Texto->Size = System::Drawing::Size(258, 66);
			this->lblTec2Texto->TabIndex = 1;
			this->lblTec2Texto->Text = L"Pantallas, botones y dibujo de sprites con GDI+.";
			// 
			// lblTec2Titulo
			// 
			this->lblTec2Titulo->Font = (gcnew System::Drawing::Font(L"Georgia", 16, System::Drawing::FontStyle::Bold));
			this->lblTec2Titulo->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lblTec2Titulo->Location = System::Drawing::Point(10, 10);
			this->lblTec2Titulo->Name = L"lblTec2Titulo";
			this->lblTec2Titulo->Size = System::Drawing::Size(258, 32);
			this->lblTec2Titulo->TabIndex = 0;
			this->lblTec2Titulo->Text = L"Windows Forms";
			// 
			// pnlTec1
			// 
			this->pnlTec1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->pnlTec1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlTec1->Controls->Add(this->lblTec1Texto);
			this->pnlTec1->Controls->Add(this->lblTec1Titulo);
			this->pnlTec1->Location = System::Drawing::Point(35, 358);
			this->pnlTec1->Name = L"pnlTec1";
			this->pnlTec1->Size = System::Drawing::Size(280, 120);
			this->pnlTec1->TabIndex = 6;
			// 
			// lblTec1Texto
			// 
			this->lblTec1Texto->Font = (gcnew System::Drawing::Font(L"Georgia", 12));
			this->lblTec1Texto->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblTec1Texto->Location = System::Drawing::Point(10, 46);
			this->lblTec1Texto->Name = L"lblTec1Texto";
			this->lblTec1Texto->Size = System::Drawing::Size(258, 66);
			this->lblTec1Texto->TabIndex = 1;
			this->lblTec1Texto->Text = L"C++/CLI en Visual Studio: toda la lógica del juego.";
			// 
			// lblTec1Titulo
			// 
			this->lblTec1Titulo->Font = (gcnew System::Drawing::Font(L"Georgia", 16, System::Drawing::FontStyle::Bold));
			this->lblTec1Titulo->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lblTec1Titulo->Location = System::Drawing::Point(10, 10);
			this->lblTec1Titulo->Name = L"lblTec1Titulo";
			this->lblTec1Titulo->Size = System::Drawing::Size(258, 32);
			this->lblTec1Titulo->TabIndex = 0;
			this->lblTec1Titulo->Text = L"Visual C++";
			// 
			// lblTecnologia
			// 
			this->lblTecnologia->Font = (gcnew System::Drawing::Font(L"Georgia", 16, System::Drawing::FontStyle::Bold));
			this->lblTecnologia->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lblTecnologia->Location = System::Drawing::Point(-1, 286);
			this->lblTecnologia->Name = L"lblTecnologia";
			this->lblTecnologia->Size = System::Drawing::Size(1000, 34);
			this->lblTecnologia->TabIndex = 5;
			this->lblTecnologia->Text = L"TECNOLOGÍA UTILIZADA";
			this->lblTecnologia->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pnlLinea
			// 
			this->pnlLinea->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(70)));
			this->pnlLinea->Location = System::Drawing::Point(299, 272);
			this->pnlLinea->Name = L"pnlLinea";
			this->pnlLinea->Size = System::Drawing::Size(400, 3);
			this->pnlLinea->TabIndex = 4;
			// 
			// lblHamp
			// 
			this->lblHamp->Font = (gcnew System::Drawing::Font(L"Georgia", 20));
			this->lblHamp->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lblHamp->Location = System::Drawing::Point(-1, 224);
			this->lblHamp->Name = L"lblHamp";
			this->lblHamp->Size = System::Drawing::Size(1000, 36);
			this->lblHamp->TabIndex = 3;
			this->lblHamp->Text = L"by hampcode";
			this->lblHamp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblNombre
			// 
			this->lblNombre->BackColor = System::Drawing::Color::Transparent;
			this->lblNombre->Font = (gcnew System::Drawing::Font(L"Georgia", 32, System::Drawing::FontStyle::Bold));
			this->lblNombre->ForeColor = System::Drawing::Color::White;
			this->lblNombre->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lblNombre.Image")));
			this->lblNombre->Location = System::Drawing::Point(-1, 108);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(1000, 118);
			this->lblNombre->TabIndex = 2;
			this->lblNombre->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblCreadoPor
			// 
			this->lblCreadoPor->Font = (gcnew System::Drawing::Font(L"Georgia", 16));
			this->lblCreadoPor->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblCreadoPor->Location = System::Drawing::Point(12, 74);
			this->lblCreadoPor->Name = L"lblCreadoPor";
			this->lblCreadoPor->Size = System::Drawing::Size(1000, 30);
			this->lblCreadoPor->TabIndex = 1;
			this->lblCreadoPor->Text = L"Creado por";
			this->lblCreadoPor->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblCreadoPor->Click += gcnew System::EventHandler(this, &FrmCreditos::lblCreadoPor_Click);
			// 
			// lblTitulo
			// 
			this->lblTitulo->Font = (gcnew System::Drawing::Font(L"Georgia", 30, System::Drawing::FontStyle::Bold));
			this->lblTitulo->ForeColor = System::Drawing::Color::LightCyan;
			this->lblTitulo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lblTitulo.Image")));
			this->lblTitulo->Location = System::Drawing::Point(9, 18);
			this->lblTitulo->Name = L"lblTitulo";
			this->lblTitulo->Size = System::Drawing::Size(1010, 56);
			this->lblTitulo->TabIndex = 0;
			this->lblTitulo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// timerScanline
			// 
			this->timerScanline->Enabled = true;
			this->timerScanline->Interval = 20;
			this->timerScanline->Tick += gcnew System::EventHandler(this, &FrmCreditos::timerScanline_Tick);
			// 
			// FrmCreditos
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(14)),
				static_cast<System::Int32>(static_cast<System::Byte>(8)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1000, 750);
			this->ControlBox = false;
			this->Controls->Add(this->pnlCapa);
			this->DoubleBuffered = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FrmCreditos";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Créditos";
			this->pnlCapa->ResumeLayout(false);
			this->pnlTec6->ResumeLayout(false);
			this->pnlTec5->ResumeLayout(false);
			this->pnlTec4->ResumeLayout(false);
			this->pnlTec3->ResumeLayout(false);
			this->pnlTec2->ResumeLayout(false);
			this->pnlTec1->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion

		System::Void btnVolver_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->Close();
		}

		System::Void btnSalir_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->DialogResult = System::Windows::Forms::DialogResult::Abort;
			this->Close();
		}
	private: System::Void lblCreadoPor_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void timerScanline_Tick(System::Object^ sender, System::EventArgs^ e) {
	pnlScanline->BringToFront();
	pnlScanline->Width = pnlScanline->Parent->ClientSize.Width;
	pnlScanline->Top += 6;

	if (pnlScanline->Top >= pnlScanline->Parent->ClientSize.Height) {
		pnlScanline->Top = -pnlScanline->Height;
	}
}
private: System::Void pnlCapa_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	System::Windows::Forms::Control^ fondo =
		safe_cast<System::Windows::Forms::Control^>(sender);

	System::Drawing::Pen^ linea = gcnew System::Drawing::Pen(
		System::Drawing::Color::FromArgb(35, 0, 0, 0));

	for (int y = 0; y < fondo->ClientSize.Height; y += 4) {
		e->Graphics->DrawLine(
			linea, 0, y, fondo->ClientSize.Width, y);
	}

	delete linea;
}
};
}
