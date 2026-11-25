#pragma once
#include "FrmPasillo.h"

namespace CrimenYCastigo2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection;

	/// <summary>
	/// Resumen de FrmJuego
	/// </summary>
	public ref class FrmJuego : public System::Windows::Forms::Form
	{
	private:
		Bitmap^ hojaSprites;
		int personajeX;
		int personajeY;
		int filaSprite;
		int columnaSprite;
		bool moviendo;
		bool arriba;
		bool abajo;
		bool izquierda;
		bool derecha;
		bool pausado;

		// Escena narrativa inicial en pantalla negra.
		Panel^ pnlEscenaNegra;
		Label^ lblTituloEscena;
		Label^ lblNarracion;
		Label^ lblInstruccionEscena;
		Panel^ pnlCajaDialogo;
		Label^ lblNombreDialogo;
		array<String^>^ textosEscena;
		String^ tituloDialogoActual;
		int indiceEscena;
		bool escenaActiva;
		bool iniciarExploracionAlFinal;

		bool llaveObtenida;
		bool nivelCompletado;
		Rectangle zonaLlave;
		Rectangle zonaPuerta;

		   Label^ lblMensajeJuego;

	public:
		FrmJuego(void)
		{
			InitializeComponent();
			this->AutoSize = false;
			this->DoubleBuffered = true;

			PropertyInfo^ propiedadBuffer = Panel::typeid->GetProperty(
				L"DoubleBuffered",
				BindingFlags::Instance | BindingFlags::NonPublic
			);

			if (propiedadBuffer != nullptr)
			{
				propiedadBuffer->SetValue(pnlSprite, true, nullptr);
				propiedadBuffer->SetValue(pnlImagenPersonaje, true, nullptr);
				propiedadBuffer->SetValue(pnlInfo, true, nullptr);
			}


			hojaSprites = nullptr;
			personajeX = 500;
			personajeY = 380;
			filaSprite = 0;      
			columnaSprite = 0;
			moviendo = false;
			arriba = abajo = izquierda = derecha = false;
			pausado = false;

			pnlEscenaNegra = nullptr;
			lblTituloEscena = nullptr;
			lblNarracion = nullptr;
			lblInstruccionEscena = nullptr;
			pnlCajaDialogo = nullptr;
			lblNombreDialogo = nullptr;
			textosEscena = nullptr;
			tituloDialogoActual = L"";
			indiceEscena = 0;
			escenaActiva = false;
			iniciarExploracionAlFinal = false;
			llaveObtenida = false;
			nivelCompletado = false;
			zonaLlave = Rectangle::Empty;
			zonaPuerta = Rectangle::Empty;
			lblMensajeJuego = nullptr;

			this->Text = L"Crimen y Castigo - Nivel 1";
			this->KeyPreview = true;
			this->BackColor = Color::FromArgb(25, 20, 20);

			pnlInfo->BackColor = Color::FromArgb(28, 22, 23);
			pnlSprite->BackColor = Color::FromArgb(65, 49, 42);

			Color colorTexto = Color::FromArgb(238, 224, 202);
			lblNombrePersonaje->ForeColor = colorTexto;
			lblTituloMisiones->ForeColor = colorTexto;
			lblListaMisiones->ForeColor = colorTexto;
			lblTituloInventario->ForeColor = colorTexto;
			lblItem1->ForeColor = colorTexto;
			lblItem2->ForeColor = colorTexto;
			lblItem3->ForeColor = colorTexto;
			lblItem4->ForeColor = colorTexto;

			lblNombrePersonaje->Text = L"RASKÓLNIKOV";
			lblTituloMisiones->Text = L"MISIÓN";
			lblListaMisiones->AutoSize = false;
			lblListaMisiones->Size = Drawing::Size(325, 95);
			lblListaMisiones->Text =
				L"- Explora la habitación\r\n"
				L"- Encuentra pistas\r\n"
				L"- Busca la llave";
			lblTituloInventario->Text = L"INVENTARIO";
			lblTituloInventario->Location = Point(33, 520);
			lblTituloInventario->ForeColor = colorTexto;
			btnPausar->BackColor = Color::FromArgb(75, 48, 38);
			btnPausar->ForeColor = Color::White;
			btnPausar->FlatStyle = FlatStyle::Flat;
			btnPausar->UseVisualStyleBackColor = false;
			lblItem1->Text = L"???";
			lblItem2->Text = L"???";
			lblItem3->Text = L"???";
			lblItem4->Text = L"???";

			pnlImagenPersonaje->BackColor = Color::FromArgb(45, 36, 34);
			pnlImgItem1->BackColor = Color::FromArgb(55, 45, 42);
			pnlImgItem2->BackColor = Color::FromArgb(55, 45, 42);
			pnlImgItem3->BackColor = Color::FromArgb(55, 45, 42);
			pnlImgItem4->BackColor = Color::FromArgb(55, 45, 42);
			pnlImgItem1->BorderStyle = BorderStyle::FixedSingle;
			pnlImgItem2->BorderStyle = BorderStyle::FixedSingle;
			pnlImgItem3->BorderStyle = BorderStyle::FixedSingle;
			pnlImgItem4->BorderStyle = BorderStyle::FixedSingle;

			lblMensajeJuego = gcnew Label();
			lblMensajeJuego->AutoSize = false;
			lblMensajeJuego->Size = Drawing::Size(760, 42);
			lblMensajeJuego->Location = Point(42, pnlSprite->ClientSize.Height - 70);
			lblMensajeJuego->BackColor = Color::FromArgb(35, 20, 15, 15);
			lblMensajeJuego->ForeColor = Color::WhiteSmoke;
			lblMensajeJuego->Font = gcnew Drawing::Font(L"Arial", 10, FontStyle::Bold);
			lblMensajeJuego->TextAlign = ContentAlignment::MiddleLeft;
			lblMensajeJuego->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
			lblMensajeJuego->Text = L"";
			pnlSprite->Controls->Add(lblMensajeJuego);
			lblMensajeJuego->BringToFront();

			try
			{
				String^ ruta = Application::StartupPath + L"\\raskonikov caminando (1).png";

				if (!System::IO::File::Exists(ruta))
					ruta = Application::StartupPath + L"\\raskolnikov_sprites.png";

				hojaSprites = gcnew Bitmap(ruta);
			}
			catch (Exception^)
			{
				MessageBox::Show(
					L"No se encontró la imagen de sprites. "
					L"Coloca raskonikov caminando (1).png o raskolnikov_sprites.png "
					L"junto al archivo ejecutable.",
					L"Falta el spritesheet",
					MessageBoxButtons::OK,
					MessageBoxIcon::Warning
				);
			}

			pnlSprite->Paint += gcnew PaintEventHandler(this, &FrmJuego::pnlSprite_Paint);
			pnlImagenPersonaje->Paint += gcnew PaintEventHandler(this, &FrmJuego::pnlImagenPersonaje_Paint);
			this->KeyDown += gcnew KeyEventHandler(this, &FrmJuego::FrmJuego_KeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &FrmJuego::FrmJuego_KeyUp);
			timer1->Interval = 100;
			timer1->Tick += gcnew EventHandler(this, &FrmJuego::timer1_Tick);
			btnPausar->Click += gcnew EventHandler(this, &FrmJuego::btnPausar_Click);

			this->Shown += gcnew EventHandler(this, &FrmJuego::FrmJuego_Shown);
			MostrarEscenaInicial();
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FrmJuego()
		{
			if (timer1 != nullptr)
				timer1->Stop();

			if (hojaSprites != nullptr)
			{
				delete hojaSprites;
				hojaSprites = nullptr;
			}

			if (components)
				delete components;
		}
	private: System::Windows::Forms::Panel^ pnlInfo;
	private: System::Windows::Forms::Panel^ pnlImagenPersonaje;
	protected:

	private: System::Windows::Forms::Panel^ pnlSprite;
	private: System::Windows::Forms::Label^ lblItem1;
	private: System::Windows::Forms::Label^ lblTituloInventario;
	private: System::Windows::Forms::Label^ lblListaMisiones;
	private: System::Windows::Forms::Label^ lblTituloMisiones;
	private: System::Windows::Forms::Label^ lblNombrePersonaje;
	private: System::Windows::Forms::Label^ lblItem2;
	private: System::Windows::Forms::Label^ lblItem4;
	private: System::Windows::Forms::Label^ lblItem3;
	private: System::Windows::Forms::Panel^ pnlImgItem1;
	private: System::Windows::Forms::Button^ btnPausar;
	private: System::Windows::Forms::Panel^ pnlImgItem4;
	private: System::Windows::Forms::Panel^ pnlImgItem3;
	private: System::Windows::Forms::Panel^ pnlImgItem2;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;


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
			this->pnlInfo = (gcnew System::Windows::Forms::Panel());
			this->pnlImgItem4 = (gcnew System::Windows::Forms::Panel());
			this->pnlImgItem3 = (gcnew System::Windows::Forms::Panel());
			this->pnlImgItem2 = (gcnew System::Windows::Forms::Panel());
			this->pnlImgItem1 = (gcnew System::Windows::Forms::Panel());
			this->btnPausar = (gcnew System::Windows::Forms::Button());
			this->lblItem4 = (gcnew System::Windows::Forms::Label());
			this->lblItem3 = (gcnew System::Windows::Forms::Label());
			this->lblItem2 = (gcnew System::Windows::Forms::Label());
			this->lblItem1 = (gcnew System::Windows::Forms::Label());
			this->lblTituloInventario = (gcnew System::Windows::Forms::Label());
			this->lblListaMisiones = (gcnew System::Windows::Forms::Label());
			this->lblTituloMisiones = (gcnew System::Windows::Forms::Label());
			this->lblNombrePersonaje = (gcnew System::Windows::Forms::Label());
			this->pnlImagenPersonaje = (gcnew System::Windows::Forms::Panel());
			this->pnlSprite = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pnlInfo->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlInfo
			// 
			this->pnlInfo->Controls->Add(this->pnlImgItem4);
			this->pnlInfo->Controls->Add(this->pnlImgItem3);
			this->pnlInfo->Controls->Add(this->pnlImgItem2);
			this->pnlInfo->Controls->Add(this->pnlImgItem1);
			this->pnlInfo->Controls->Add(this->btnPausar);
			this->pnlInfo->Controls->Add(this->lblItem4);
			this->pnlInfo->Controls->Add(this->lblItem3);
			this->pnlInfo->Controls->Add(this->lblItem2);
			this->pnlInfo->Controls->Add(this->lblItem1);
			this->pnlInfo->Controls->Add(this->lblTituloInventario);
			this->pnlInfo->Controls->Add(this->lblListaMisiones);
			this->pnlInfo->Controls->Add(this->lblTituloMisiones);
			this->pnlInfo->Controls->Add(this->lblNombrePersonaje);
			this->pnlInfo->Controls->Add(this->pnlImagenPersonaje);
			this->pnlInfo->Dock = System::Windows::Forms::DockStyle::Right;
			this->pnlInfo->Location = System::Drawing::Point(1126, 0);
			this->pnlInfo->Margin = System::Windows::Forms::Padding(2);
			this->pnlInfo->Name = L"pnlInfo";
			this->pnlInfo->Size = System::Drawing::Size(300, 839);
			this->pnlInfo->TabIndex = 0;
			// 
			// pnlImgItem4
			// 
			this->pnlImgItem4->Location = System::Drawing::Point(171, 521);
			this->pnlImgItem4->Margin = System::Windows::Forms::Padding(2);
			this->pnlImgItem4->Name = L"pnlImgItem4";
			this->pnlImgItem4->Size = System::Drawing::Size(75, 81);
			this->pnlImgItem4->TabIndex = 13;
			// 
			// pnlImgItem3
			// 
			this->pnlImgItem3->Location = System::Drawing::Point(46, 521);
			this->pnlImgItem3->Margin = System::Windows::Forms::Padding(2);
			this->pnlImgItem3->Name = L"pnlImgItem3";
			this->pnlImgItem3->Size = System::Drawing::Size(75, 81);
			this->pnlImgItem3->TabIndex = 12;
			// 
			// pnlImgItem2
			// 
			this->pnlImgItem2->Location = System::Drawing::Point(171, 400);
			this->pnlImgItem2->Margin = System::Windows::Forms::Padding(2);
			this->pnlImgItem2->Name = L"pnlImgItem2";
			this->pnlImgItem2->Size = System::Drawing::Size(75, 81);
			this->pnlImgItem2->TabIndex = 11;
			// 
			// pnlImgItem1
			// 
			this->pnlImgItem1->Location = System::Drawing::Point(47, 400);
			this->pnlImgItem1->Margin = System::Windows::Forms::Padding(2);
			this->pnlImgItem1->Name = L"pnlImgItem1";
			this->pnlImgItem1->Size = System::Drawing::Size(75, 81);
			this->pnlImgItem1->TabIndex = 10;
			// 
			// btnPausar
			// 
			this->btnPausar->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			this->btnPausar->Location = System::Drawing::Point(71, 633);
			this->btnPausar->Margin = System::Windows::Forms::Padding(2);
			this->btnPausar->Name = L"btnPausar";
			this->btnPausar->Size = System::Drawing::Size(149, 35);
			this->btnPausar->TabIndex = 9;
			this->btnPausar->Text = L"PAUSAR";
			this->btnPausar->UseVisualStyleBackColor = true;
			// 
			// lblItem4
			// 
			this->lblItem4->AutoSize = true;
			this->lblItem4->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblItem4->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblItem4->Location = System::Drawing::Point(195, 605);
			this->lblItem4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblItem4->Name = L"lblItem4";
			this->lblItem4->Size = System::Drawing::Size(38, 18);
			this->lblItem4->TabIndex = 8;
			this->lblItem4->Text = L"\?\?\?";
			this->lblItem4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblItem4->Click += gcnew System::EventHandler(this, &FrmJuego::lblItem4_Click);
			// 
			// lblItem3
			// 
			this->lblItem3->AutoSize = true;
			this->lblItem3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblItem3->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblItem3->Location = System::Drawing::Point(67, 605);
			this->lblItem3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblItem3->Name = L"lblItem3";
			this->lblItem3->Size = System::Drawing::Size(38, 18);
			this->lblItem3->TabIndex = 7;
			this->lblItem3->Text = L"\?\?\?";
			this->lblItem3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblItem3->Click += gcnew System::EventHandler(this, &FrmJuego::lblItem3_Click);
			// 
			// lblItem2
			// 
			this->lblItem2->AutoSize = true;
			this->lblItem2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblItem2->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblItem2->Location = System::Drawing::Point(195, 487);
			this->lblItem2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblItem2->Name = L"lblItem2";
			this->lblItem2->Size = System::Drawing::Size(38, 18);
			this->lblItem2->TabIndex = 6;
			this->lblItem2->Text = L"\?\?\?";
			this->lblItem2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblItem2->Click += gcnew System::EventHandler(this, &FrmJuego::lblItem2_Click);
			// 
			// lblItem1
			// 
			this->lblItem1->AutoSize = true;
			this->lblItem1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblItem1->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblItem1->Location = System::Drawing::Point(67, 487);
			this->lblItem1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblItem1->Name = L"lblItem1";
			this->lblItem1->Size = System::Drawing::Size(38, 18);
			this->lblItem1->TabIndex = 5;
			this->lblItem1->Text = L"\?\?\?";
			this->lblItem1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblItem1->Click += gcnew System::EventHandler(this, &FrmJuego::lblItem1_Click);
			// 
			// lblTituloInventario
			// 
			this->lblTituloInventario->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->lblTituloInventario->AutoSize = true;
			this->lblTituloInventario->Cursor = System::Windows::Forms::Cursors::Hand;
			this->lblTituloInventario->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblTituloInventario->Font = (gcnew System::Drawing::Font(L"Courier New", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTituloInventario->Location = System::Drawing::Point(80, 696);
			this->lblTituloInventario->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblTituloInventario->Name = L"lblTituloInventario";
			this->lblTituloInventario->Size = System::Drawing::Size(140, 23);
			this->lblTituloInventario->TabIndex = 4;
			this->lblTituloInventario->Text = L"INVENTARIO";
			this->lblTituloInventario->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblListaMisiones
			// 
			this->lblListaMisiones->AutoSize = true;
			this->lblListaMisiones->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblListaMisiones->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblListaMisiones->Location = System::Drawing::Point(25, 330);
			this->lblListaMisiones->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblListaMisiones->Name = L"lblListaMisiones";
			this->lblListaMisiones->Size = System::Drawing::Size(58, 54);
			this->lblListaMisiones->TabIndex = 3;
			this->lblListaMisiones->Text = L"- \?\?\?\r\n- \?\?\?\r\n- \?\?\?";
			// 
			// lblTituloMisiones
			// 
			this->lblTituloMisiones->AutoSize = true;
			this->lblTituloMisiones->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblTituloMisiones->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTituloMisiones->Location = System::Drawing::Point(24, 289);
			this->lblTituloMisiones->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblTituloMisiones->Name = L"lblTituloMisiones";
			this->lblTituloMisiones->Size = System::Drawing::Size(98, 18);
			this->lblTituloMisiones->TabIndex = 2;
			this->lblTituloMisiones->Text = L"Misiones:";
			this->lblTituloMisiones->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblNombrePersonaje
			// 
			this->lblNombrePersonaje->AutoSize = true;
			this->lblNombrePersonaje->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->lblNombrePersonaje->Font = (gcnew System::Drawing::Font(L"Courier New", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNombrePersonaje->Location = System::Drawing::Point(108, 36);
			this->lblNombrePersonaje->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblNombrePersonaje->Name = L"lblNombrePersonaje";
			this->lblNombrePersonaje->Size = System::Drawing::Size(90, 25);
			this->lblNombrePersonaje->TabIndex = 1;
			this->lblNombrePersonaje->Text = L"NOMBRE";
			this->lblNombrePersonaje->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pnlImagenPersonaje
			// 
			this->pnlImagenPersonaje->Location = System::Drawing::Point(60, 72);
			this->pnlImagenPersonaje->Margin = System::Windows::Forms::Padding(2);
			this->pnlImagenPersonaje->Name = L"pnlImagenPersonaje";
			this->pnlImagenPersonaje->Size = System::Drawing::Size(188, 203);
			this->pnlImagenPersonaje->TabIndex = 0;
			// 
			// pnlSprite
			// 
			this->pnlSprite->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlSprite->Location = System::Drawing::Point(0, 0);
			this->pnlSprite->Margin = System::Windows::Forms::Padding(2);
			this->pnlSprite->Name = L"pnlSprite";
			this->pnlSprite->Size = System::Drawing::Size(1126, 839);
			this->pnlSprite->TabIndex = 1;
			// 
			// FrmJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1426, 839);
			this->Controls->Add(this->pnlSprite);
			this->Controls->Add(this->pnlInfo);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"FrmJuego";
			this->Text = L"FrmJuego";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->pnlInfo->ResumeLayout(false);
			this->pnlInfo->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
	
		void MostrarEscenaInicial()
		{
			array<String^>^ lineas = gcnew array<String^>
			{
				L"¿Por qué algunos nacen con una mesa llena y otros deben elegir entre comer o pagar el alquiler?\r\nNo recuerdo haber elegido esta vida. Sin embargo, parece que debo disculparme por tenerla.",
					L"Hay personas que hablan de esfuerzo como si todos empezáramos desde el mismo lugar.\r\nEllos tienen puertas abiertas. Yo apenas encuentro una rendija por donde respirar.",
					L"La pobreza no solo vacía los bolsillos. También obliga a bajar la mirada,\r\na agradecer migajas y a fingir que la humillación no duele.",
					L"Me digo que soy distinto. Que mi inteligencia debería bastar para cambiar mi destino.\r\nPero ¿de qué sirve pensar tanto cuando ni siquiera puedo resolver el día de mañana?",
					L"Quizá la vida sea injusta. Quizá siempre lo haya sido.\r\nLo insoportable es que todos parecen acostumbrados, como si el sufrimiento de unos\r\nfuera el precio natural de la comodidad de otros.",
					L"No quiero compasión. Estoy cansado de que me miren como si mi pobreza fuera una culpa.\r\nPero tampoco puedo seguir encerrado, alimentando pensamientos que me consumen.",
					L"Necesito aire. Necesito caminar, observar, encontrar una salida a esta miseria.\r\nTal vez afuera encuentre una respuesta. O al menos una razón para continuar.",
					L"Basta de esconderme. La puerta está ahí.\r\nPrimero debo encontrar la llave. Después, salir de esta habitación."
			};

			IniciarDialogo(lineas, L"CAPÍTULO I — PENSAMIENTOS DE RASKÓLNIKOV", true);
		}

		void IniciarDialogo(array<String^>^ lineas, String^ titulo, bool comenzarExploracionAlTerminar)
		{
			if (lineas == nullptr || lineas->Length == 0)
				return;

			timer1->Stop();
			arriba = abajo = izquierda = derecha = false;
			textosEscena = lineas;
			tituloDialogoActual = titulo;
			indiceEscena = 0;
			escenaActiva = true;
			iniciarExploracionAlFinal = comenzarExploracionAlTerminar;

			if (pnlEscenaNegra == nullptr)
			{
				pnlEscenaNegra = gcnew Panel();
				pnlEscenaNegra->Dock = DockStyle::Fill;
				pnlEscenaNegra->BackColor = Color::Black;

				lblTituloEscena = gcnew Label();
				lblTituloEscena->AutoSize = false;
				lblTituloEscena->BackColor = Color::Black;
				lblTituloEscena->ForeColor = Color::FromArgb(190, 155, 125);
				lblTituloEscena->Font = gcnew Drawing::Font(L"Georgia", 15, FontStyle::Bold);
				lblTituloEscena->TextAlign = ContentAlignment::MiddleCenter;

				pnlCajaDialogo = gcnew Panel();
				pnlCajaDialogo->BackColor = Color::FromArgb(22, 19, 20);
				pnlCajaDialogo->BorderStyle = BorderStyle::FixedSingle;

				lblNombreDialogo = gcnew Label();
				lblNombreDialogo->AutoSize = false;
				lblNombreDialogo->BackColor = Color::FromArgb(22, 19, 20);
				lblNombreDialogo->ForeColor = Color::FromArgb(211, 173, 130);
				lblNombreDialogo->Font = gcnew Drawing::Font(L"Georgia", 12, FontStyle::Bold);
				lblNombreDialogo->TextAlign = ContentAlignment::MiddleLeft;
				lblNombreDialogo->Text = L"RASKÓLNIKOV  ·  PENSAMIENTO";

				lblNarracion = gcnew Label();
				lblNarracion->AutoSize = false;
				lblNarracion->BackColor = Color::FromArgb(22, 19, 20);
				lblNarracion->ForeColor = Color::Gainsboro;
				lblNarracion->Font = gcnew Drawing::Font(L"Georgia", 16, FontStyle::Regular);
				lblNarracion->TextAlign = ContentAlignment::MiddleLeft;

				lblInstruccionEscena = gcnew Label();
				lblInstruccionEscena->AutoSize = false;
				lblInstruccionEscena->BackColor = Color::FromArgb(22, 19, 20);
				lblInstruccionEscena->ForeColor = Color::FromArgb(145, 145, 145);
				lblInstruccionEscena->Font = gcnew Drawing::Font(L"Arial", 10, FontStyle::Regular);
				lblInstruccionEscena->TextAlign = ContentAlignment::MiddleRight;

				pnlCajaDialogo->Controls->Add(lblNombreDialogo);
				pnlCajaDialogo->Controls->Add(lblNarracion);
				pnlCajaDialogo->Controls->Add(lblInstruccionEscena);
				pnlEscenaNegra->Controls->Add(lblTituloEscena);
				pnlEscenaNegra->Controls->Add(pnlCajaDialogo);

				pnlEscenaNegra->Click += gcnew EventHandler(this, &FrmJuego::AvanzarEscenaInicial);
				pnlCajaDialogo->Click += gcnew EventHandler(this, &FrmJuego::AvanzarEscenaInicial);
				lblTituloEscena->Click += gcnew EventHandler(this, &FrmJuego::AvanzarEscenaInicial);
				lblNombreDialogo->Click += gcnew EventHandler(this, &FrmJuego::AvanzarEscenaInicial);
				lblNarracion->Click += gcnew EventHandler(this, &FrmJuego::AvanzarEscenaInicial);
				lblInstruccionEscena->Click += gcnew EventHandler(this, &FrmJuego::AvanzarEscenaInicial);
				pnlEscenaNegra->Resize += gcnew EventHandler(this, &FrmJuego::AcomodarEscenaInicial);

				this->Controls->Add(pnlEscenaNegra);
			}

			pnlEscenaNegra->Visible = true;
			pnlEscenaNegra->BringToFront();
			AcomodarEscenaInicial(nullptr, nullptr);
			ActualizarTextoEscena();
			this->Activate();
			this->Focus();
		}

		void AcomodarEscenaInicial(Object^ sender, EventArgs^ e)
		{
			if (pnlEscenaNegra == nullptr || lblTituloEscena == nullptr ||
				pnlCajaDialogo == nullptr || lblNombreDialogo == nullptr ||
				lblNarracion == nullptr || lblInstruccionEscena == nullptr)
				return;

			int ancho = pnlEscenaNegra->ClientSize.Width;
			int alto = pnlEscenaNegra->ClientSize.Height;
			int margen = 55;
			int anchoCaja = Math::Max(450, ancho - margen * 2);
			int altoCaja = 285;

			lblTituloEscena->Size = Drawing::Size(anchoCaja, 65);
			lblTituloEscena->Location = Point(margen, Math::Max(35, alto / 2 - 245));
			pnlCajaDialogo->Size = Drawing::Size(anchoCaja, altoCaja);
			pnlCajaDialogo->Location = Point(margen, alto - altoCaja - 65);

			lblNombreDialogo->Location = Point(25, 15);
			lblNombreDialogo->Size = Drawing::Size(anchoCaja - 50, 32);
			lblNarracion->Location = Point(25, 55);
			lblNarracion->Size = Drawing::Size(anchoCaja - 50, 155);
			lblInstruccionEscena->Location = Point(25, 218);
			lblInstruccionEscena->Size = Drawing::Size(anchoCaja - 50, 40);
		}

		void ActualizarTextoEscena()
		{
			if (textosEscena == nullptr || indiceEscena < 0 || indiceEscena >= textosEscena->Length)
				return;

			lblTituloEscena->Text = tituloDialogoActual;
			lblNarracion->Text = textosEscena[indiceEscena];
			lblInstruccionEscena->Text = L"ENTER / ESPACIO / CLIC    " +
				(indiceEscena + 1).ToString() + L" / " + textosEscena->Length.ToString();
		}

		void AvanzarEscenaInicial(Object^ sender, EventArgs^ e)
		{
			if (!escenaActiva)
				return;

			indiceEscena++;
			if (indiceEscena < textosEscena->Length)
			{
				ActualizarTextoEscena();
				return;
			}

			bool iniciarJuego = iniciarExploracionAlFinal;
			escenaActiva = false;
			pnlEscenaNegra->Visible = false;
			pnlEscenaNegra->SendToBack();

			if (iniciarJuego)
				IniciarFaseExploracion();
			else if (!nivelCompletado)
				timer1->Start(); 
		}

		void ActualizarMisiones()
		{
			if (nivelCompletado)
				lblListaMisiones->Text = L"[X] Encuentra la llave\r\n[X] Sal de la habitación";
			else if (llaveObtenida)
				lblListaMisiones->Text = L"[X] Encuentra la llave\r\n[ ] Sal de la habitación";
			else
				lblListaMisiones->Text = L"[ ] Encuentra la llave\r\n[ ] Sal de la habitación";
		}

		void IniciarFaseExploracion()
		{
			llaveObtenida = false;
			nivelCompletado = false;
			personajeX = pnlSprite->ClientSize.Width / 2 - 55;
			personajeY = pnlSprite->ClientSize.Height / 2 - 70;
			filaSprite = 0;
			columnaSprite = 0;

			zonaLlave = Rectangle(pnlSprite->ClientSize.Width - 285, 155, 44, 44);
			zonaPuerta = Rectangle(pnlSprite->ClientSize.Width / 2 - 58,
				pnlSprite->ClientSize.Height - 130, 116, 100);

			lblTituloMisiones->Text = L"MISIÓN";
			ActualizarMisiones();
			lblItem1->Text = L"???";
			pnlImgItem1->BackColor = Color::FromArgb(55, 45, 42);
			lblMensajeJuego->Text = L"Objetivo: encuentra la llave sobre el escritorio. Pulsa E para examinar.";
			timer1->Start();
			pnlSprite->Invalidate();
			this->Activate();
			this->Focus();
		}

		void Interactuar()
		{
			if (escenaActiva || nivelCompletado)
				return;

			Rectangle jugador(personajeX + 20, personajeY + 25, 70, 95);
			jugador.Inflate(55, 55);

			if (!llaveObtenida && jugador.IntersectsWith(zonaLlave))
			{
				llaveObtenida = true;
				lblItem1->Text = L"LLAVE";
				pnlImgItem1->BackColor = Color::FromArgb(119, 87, 42);
				lblMensajeJuego->Text = L"Has encontrado una llave antigua. Ahora puedes intentar abrir la puerta.";
				ActualizarMisiones();
				pnlSprite->Invalidate();
				return;
			}

			if (jugador.IntersectsWith(zonaPuerta))
			{
				if (!llaveObtenida)
					lblMensajeJuego->Text = L"La puerta está cerrada. Primero encuentra la llave sobre el escritorio.";
				else
				{
					nivelCompletado = true;
					timer1->Stop();
					arriba = abajo = izquierda = derecha = false;

					ActualizarMisiones();

					array<String^>^ cierre = gcnew array<String^>
					{
						L"La llave gira con dificultad. La puerta cede y una corriente helada\r\n"
							L"recorre el pasillo. Raskólnikov permanece inmóvil durante un instante.",
							L"No ha resuelto su pobreza. Tampoco ha encontrado respuestas.\r\n"
							L"Pero por primera vez en mucho tiempo ha logrado salir de aquella habitación.",
							L"Afuera lo espera una ciudad indiferente. Y, dentro de él, preguntas\r\n"
							L"que todavía no sabe cómo responder. El día apenas comienza."


					};

					FrmPasillo^ pasillo = gcnew FrmPasillo(llaveObtenida);
					pasillo->ShowDialog(this);
					delete pasillo;


					IniciarDialogo(cierre, L"CAPÍTULO I — LA SALIDA", false);
				}
				return;
			}

			lblMensajeJuego->Text = L"No hay nada que examinar aquí. Acércate al escritorio o a la puerta.";
		}

		void DibujarPersonaje(Graphics^ g, Rectangle destino)
		{
			if (hojaSprites == nullptr)
			{
				SolidBrush^ b = gcnew SolidBrush(Color::SaddleBrown);
				g->FillEllipse(b, destino);
				delete b;
				g->DrawString(L"R", gcnew Drawing::Font(L"Arial", 18, FontStyle::Bold),
					Brushes::White, destino.X + 38, destino.Y + 45);
				return;
			}

			int anchoCelda = hojaSprites->Width / 4;
			int altoCelda = hojaSprites->Height / 4;
			if (anchoCelda <= 0 || altoCelda <= 0)
				return;

			filaSprite = Math::Max(0, Math::Min(filaSprite, 3));
			columnaSprite = Math::Max(0, Math::Min(columnaSprite, 3));

			Rectangle origen(
				columnaSprite * anchoCelda,
				filaSprite * altoCelda,
				anchoCelda,
				altoCelda
			);

			g->InterpolationMode = Drawing2D::InterpolationMode::NearestNeighbor;
			g->PixelOffsetMode = Drawing2D::PixelOffsetMode::Half;
			g->DrawImage(hojaSprites, destino, origen, GraphicsUnit::Pixel);
		}

		System::Void FrmJuego_Shown(Object^ sender, EventArgs^ e)
		{
			pnlSprite->Invalidate();
			pnlImagenPersonaje->Invalidate();

		
			this->Activate();
			this->Focus();
		}

		System::Void pnlSprite_Paint(Object^ sender, PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;

			g->Clear(Color::FromArgb(56, 42, 36));
			g->SmoothingMode = Drawing2D::SmoothingMode::None;
			g->InterpolationMode = Drawing2D::InterpolationMode::NearestNeighbor;
			g->PixelOffsetMode = Drawing2D::PixelOffsetMode::Half;

			int ancho = pnlSprite->ClientSize.Width;
			int alto = pnlSprite->ClientSize.Height;

			SolidBrush^ suelo = gcnew SolidBrush(Color::FromArgb(88, 65, 51));
			g->FillRectangle(suelo, 0, 0, ancho, alto);
			delete suelo;

			Pen^ lineaPiso = gcnew Pen(Color::FromArgb(111, 82, 63), 2);
			for (int y = 55; y < alto; y += 78)
				g->DrawLine(lineaPiso, 0, y, ancho, y);
			for (int x = 40; x < ancho; x += 115)
				g->DrawLine(lineaPiso, x, 0, x, alto);
			delete lineaPiso;

			SolidBrush^ pared = gcnew SolidBrush(Color::FromArgb(43, 32, 30));
			g->FillRectangle(pared, 0, 0, ancho, 28);
			g->FillRectangle(pared, 0, 0, 28, alto);
			g->FillRectangle(pared, ancho - 28, 0, 28, alto);
			g->FillRectangle(pared, 0, alto - 28, ancho, 28);
			delete pared;

			SolidBrush^ mueble = gcnew SolidBrush(Color::FromArgb(52, 35, 30));
			SolidBrush^ manta = gcnew SolidBrush(Color::FromArgb(119, 105, 91));
			g->FillRectangle(mueble, 105, 115, 285, 360);
			g->FillRectangle(manta, 125, 135, 245, 270);
			g->DrawRectangle(Pens::SaddleBrown, 105, 115, 285, 360);

			g->FillRectangle(mueble, ancho - 390, 120, 250, 115);
			g->FillRectangle(mueble, ancho - 230, 260, 120, 300);

			SolidBrush^ alfombra = gcnew SolidBrush(Color::FromArgb(91, 48, 39));
			g->FillRectangle(alfombra, ancho / 2 - 170, alto - 280, 340, 170);
			g->DrawRectangle(Pens::Sienna, ancho / 2 - 170, alto - 280, 340, 170);

			delete alfombra;
			delete manta;
			delete mueble;

			// Puerta de salida.
			SolidBrush^ puerta = gcnew SolidBrush(Color::FromArgb(78, 43, 29));
			Rectangle dibujoPuerta(ancho / 2 - 48, alto - 80, 96, 52);
			g->FillRectangle(puerta, dibujoPuerta);
			g->DrawRectangle(Pens::SandyBrown, dibujoPuerta);
			g->FillEllipse(Brushes::Goldenrod, dibujoPuerta.Right - 18, dibujoPuerta.Y + 25, 6, 6);
			delete puerta;

			if (!llaveObtenida && zonaLlave.Width > 0)
			{
				Pen^ oro = gcnew Pen(Color::FromArgb(245, 194, 76), 5);
				g->DrawEllipse(oro, zonaLlave.X + 3, zonaLlave.Y + 2, 17, 17);
				g->DrawLine(oro, zonaLlave.X + 19, zonaLlave.Y + 19, zonaLlave.X + 39, zonaLlave.Y + 39);
				g->DrawLine(oro, zonaLlave.X + 29, zonaLlave.Y + 29, zonaLlave.X + 34, zonaLlave.Y + 24);
				g->DrawLine(oro, zonaLlave.X + 35, zonaLlave.Y + 35, zonaLlave.X + 40, zonaLlave.Y + 30);
				delete oro;
			}
			g->DrawString(L"SALIDA", gcnew Drawing::Font(L"Arial", 9, FontStyle::Bold),
				Brushes::WhiteSmoke, dibujoPuerta.X + 18, dibujoPuerta.Y + 4);

			Drawing::Font^ fuente = gcnew Drawing::Font(
				L"Arial", 11, FontStyle::Bold
			);
			g->DrawString(
				L"Muévete con WASD o las flechas",
				fuente,
				Brushes::WhiteSmoke,
				42,
				42
			);
			delete fuente;

			// Personaje. Se vuelve a dibujar únicamente en el buffer del panel.
			DibujarPersonaje(g, Rectangle(personajeX, personajeY, 240, 285));
		}

		System::Void pnlImagenPersonaje_Paint(Object^ sender, PaintEventArgs^ e)
		{
			if (hojaSprites != nullptr)
			{
				Rectangle origen(0, 0, hojaSprites->Width / 4, hojaSprites->Height / 4);
				e->Graphics->DrawImage(hojaSprites, pnlImagenPersonaje->ClientRectangle,
					origen, GraphicsUnit::Pixel);
			}
			else
			{
				e->Graphics->DrawString(L"R", gcnew Drawing::Font(L"Georgia", 48, FontStyle::Bold),
					Brushes::Gainsboro, 80, 65);
			}
		}

		System::Void FrmJuego_KeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (escenaActiva)
			{
				if (e->KeyCode == Keys::Enter || e->KeyCode == Keys::Space)
				{
					AvanzarEscenaInicial(nullptr, nullptr);
					e->SuppressKeyPress = true;
				}
				return;
			}

			if (pausado) return;

			if (e->KeyCode == Keys::E)
			{
				Interactuar();
				e->SuppressKeyPress = true;
				return;
			}

			if (e->KeyCode == Keys::W || e->KeyCode == Keys::Up) arriba = true;
			if (e->KeyCode == Keys::S || e->KeyCode == Keys::Down) abajo = true;
			if (e->KeyCode == Keys::A || e->KeyCode == Keys::Left) izquierda = true;
			if (e->KeyCode == Keys::D || e->KeyCode == Keys::Right) derecha = true;
		}

		System::Void FrmJuego_KeyUp(Object^ sender, KeyEventArgs^ e)
		{
			if (escenaActiva)
				return;

			if (e->KeyCode == Keys::W || e->KeyCode == Keys::Up) arriba = false;
			if (e->KeyCode == Keys::S || e->KeyCode == Keys::Down) abajo = false;
			if (e->KeyCode == Keys::A || e->KeyCode == Keys::Left) izquierda = false;
			if (e->KeyCode == Keys::D || e->KeyCode == Keys::Right) derecha = false;
		}

		System::Void timer1_Tick(Object^ sender, EventArgs^ e)
		{
			if (pausado || nivelCompletado || escenaActiva) return;

			moviendo = false;

			if (arriba)
			{
				personajeY -= 15;
				filaSprite = 3;
				moviendo = true;
			}
			else if (abajo)
			{
				personajeY += 15;
				filaSprite = 0;
				moviendo = true;
			}
			else if (izquierda)
			{
				personajeX -= 15;
				filaSprite = 2;
				moviendo = true;
			}
			else if (derecha)
			{
				personajeX += 15;
				filaSprite = 1;
				moviendo = true;
			}

			// No repintar el escenario cuando el personaje está quieto.
			if (!moviendo)
				return;

			int maxX = Math::Max(28, pnlSprite->ClientSize.Width - 138);
			int maxY = Math::Max(28, pnlSprite->ClientSize.Height - 173);
			personajeX = Math::Max(28, Math::Min(personajeX, maxX));
			personajeY = Math::Max(28, Math::Min(personajeY, maxY));

			columnaSprite = (columnaSprite + 1) % 4;
			pnlSprite->Invalidate();
		}

		System::Void btnPausar_Click(Object^ sender, EventArgs^ e)
		{
			pausado = !pausado;
			btnPausar->Text = pausado ? L"CONTINUAR" : L"PAUSAR";
			if (pausado)
			{
				timer1->Stop();
				arriba = abajo = izquierda = derecha = false;
			}
			else
			{
				timer1->Start();
				this->Activate();
				this->Focus();
			}
		}

	private:
		System::Void lblItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		}
	private: System::Void lblItem3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lblItem4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lblItem2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
