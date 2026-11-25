#pragma once

#include "FrmCuartoAliona.h"

namespace CrimenYCastigo2 {

	// Panel con doble búfer para evitar parpadeos al redibujar la escena.
	public ref class PanelDobleBuffer : public System::Windows::Forms::Panel
	{
	public:
		PanelDobleBuffer()
		{
			this->DoubleBuffered = true;
			this->ResizeRedraw = true;
			this->SetStyle(
				System::Windows::Forms::ControlStyles::AllPaintingInWmPaint |
				System::Windows::Forms::ControlStyles::UserPaint |
				System::Windows::Forms::ControlStyles::OptimizedDoubleBuffer,
				true);
			this->UpdateStyles();
		}
	};

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Reflection;

	/// <summary>
	/// </summary>
	public ref class FrmPasillo : public System::Windows::Forms::Form
	{
	private:
		Panel^ pnlEscenario;
		Panel^ pnlInfo;
		Panel^ pnlDialogo;
		Label^ lblNombre;
		Label^ lblTituloMision;
		Label^ lblMision;
		Label^ lblTituloInventario;
		Label^ lblLlave;
		Label^ lblMensaje;
		Label^ lblTituloDialogo;
		Label^ lblTextoDialogo;
		Label^ lblInstruccionDialogo;
		Button^ btnPausar;
		Timer^ timerPasillo;

		Bitmap^ hojaSprites;
		int personajeX;
		int personajeY;
		int filaSprite;
		int columnaSprite;
		bool arriba;
		bool abajo;
		bool izquierda;
		bool derecha;
		bool moviendo;
		bool pausado;
		bool llaveObtenida;
		bool cuartoAlionaVisitado;
		bool dialogoActivo;
		bool cerrarAlTerminar;
		int indiceDialogo;
		array<String^>^ textosDialogo;
		String^ tituloActual;

		Rectangle zonaPuertaIzquierda;
		Rectangle zonaPuertaDerecha;
		Rectangle zonaEscaleras;

	public:
		FrmPasillo(bool tieneLaLlave)
		{
			// Inicializar primero el estado que usa la interfaz del inventario.
			llaveObtenida = tieneLaLlave;
			InitializeInterfaz();
			cuartoAlionaVisitado = false;
			hojaSprites = nullptr;
			personajeX = 0;
			personajeY = 0;
			filaSprite = 0;
			columnaSprite = 0;
			arriba = abajo = izquierda = derecha = false;
			moviendo = false;
			pausado = false;
			dialogoActivo = false;
			cerrarAlTerminar = false;
			indiceDialogo = 0;
			textosDialogo = nullptr;
			tituloActual = L"";

			this->Text = L"Crimen y Castigo - Pasillo";
			this->BackColor = Color::FromArgb(22, 18, 18);
			this->KeyPreview = true;
			this->DoubleBuffered = true;
			this->WindowState = FormWindowState::Maximized;
			this->StartPosition = FormStartPosition::CenterScreen;

			CargarSprites();
			ActualizarZonas();
			ActualizarInterfaz();

			timerPasillo->Interval = 100;
			timerPasillo->Tick += gcnew EventHandler(this, &FrmPasillo::timerPasillo_Tick);
			pnlEscenario->Paint += gcnew PaintEventHandler(this, &FrmPasillo::pnlEscenario_Paint);
			this->KeyDown += gcnew KeyEventHandler(this, &FrmPasillo::FrmPasillo_KeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &FrmPasillo::FrmPasillo_KeyUp);
			this->Resize += gcnew EventHandler(this, &FrmPasillo::FrmPasillo_Resize);
			this->Deactivate += gcnew EventHandler(this, &FrmPasillo::FrmPasillo_Deactivate);
			this->Shown += gcnew EventHandler(this, &FrmPasillo::FrmPasillo_Shown);
			btnPausar->Click += gcnew EventHandler(this, &FrmPasillo::btnPausar_Click);

			MostrarDialogo(
				gcnew array<String^>
			{
				L"La puerta de la habitación se cierra detrás de mí. El pasillo es estrecho y apenas está iluminado.",
					L"A ambos lados hay puertas cerradas. Desde algún lugar llega el sonido de pasos y una conversación lejana.",
					L"No debo quedarme aquí. Al fondo se distinguen las escaleras. Tengo que llegar hasta ellas y salir del edificio."
			},
				L"CAPÍTULO I — EL PASILLO",
				false
			);
		}

	protected:
		~FrmPasillo()
		{
			if (timerPasillo != nullptr)
				timerPasillo->Stop();

			if (hojaSprites != nullptr)
			{
				delete hojaSprites;
				hojaSprites = nullptr;
			}
		}

	private:
		void InitializeInterfaz()
		{
			this->ClientSize = Drawing::Size(1500, 850);

			pnlEscenario = gcnew PanelDobleBuffer();
			pnlEscenario->Dock = DockStyle::Fill;
			pnlEscenario->BackColor = Color::FromArgb(45, 35, 32);
			pnlEscenario->TabStop = false;

			pnlInfo = gcnew Panel();
			pnlInfo->Dock = DockStyle::Right;
			pnlInfo->Width = 340;
			pnlInfo->BackColor = Color::FromArgb(28, 22, 23);

			lblNombre = gcnew Label();
			lblNombre->Text = L"RASKÓLNIKOV";
			lblNombre->Font = gcnew Drawing::Font(L"Courier New", 17, FontStyle::Bold);
			lblNombre->ForeColor = Color::FromArgb(238, 224, 202);
			lblNombre->TextAlign = ContentAlignment::MiddleCenter;
			lblNombre->Location = Point(20, 35);
			lblNombre->Size = Drawing::Size(300, 40);

			lblTituloMision = gcnew Label();
			lblTituloMision->Text = L"MISIÓN";
			lblTituloMision->Font = gcnew Drawing::Font(L"Courier New", 13, FontStyle::Bold);
			lblTituloMision->ForeColor = Color::FromArgb(211, 173, 130);
			lblTituloMision->Location = Point(30, 365);
			lblTituloMision->Size = Drawing::Size(280, 30);

			lblMision = gcnew Label();
			lblMision->Text = L"[X] Sal de la habitación\r\n[ ] Visita a Aliona\r\n[ ] Llega a las escaleras";
			lblMision->Font = gcnew Drawing::Font(L"Courier New", 11, FontStyle::Bold);
			lblMision->ForeColor = Color::FromArgb(238, 224, 202);
			lblMision->Location = Point(30, 405);
			lblMision->Size = Drawing::Size(285, 105);

			lblTituloInventario = gcnew Label();
			lblTituloInventario->Text = L"INVENTARIO";
			lblTituloInventario->Font = gcnew Drawing::Font(L"Courier New", 13, FontStyle::Bold);
			lblTituloInventario->ForeColor = Color::FromArgb(211, 173, 130);
			lblTituloInventario->Location = Point(30, 550);
			lblTituloInventario->Size = Drawing::Size(280, 30);

			lblLlave = gcnew Label();
			lblLlave->Text = llaveObtenida ? L"◆  LLAVE ANTIGUA" : L"◆  SIN LLAVE";
			lblLlave->Font = gcnew Drawing::Font(L"Courier New", 11, FontStyle::Bold);
			lblLlave->ForeColor = llaveObtenida ? Color::FromArgb(231, 188, 91) : Color::Silver;
			lblLlave->Location = Point(30, 595);
			lblLlave->Size = Drawing::Size(280, 35);

			btnPausar = gcnew Button();
			btnPausar->Text = L"PAUSAR";
			btnPausar->Location = Point(65, 760);
			btnPausar->Size = Drawing::Size(210, 45);
			btnPausar->BackColor = Color::FromArgb(75, 48, 38);
			btnPausar->ForeColor = Color::White;
			btnPausar->FlatStyle = FlatStyle::Flat;
			btnPausar->UseVisualStyleBackColor = false;
			btnPausar->TabStop = false;

			lblMensaje = gcnew Label();
			lblMensaje->AutoSize = false;
			lblMensaje->Location = Point(35, 0);
			lblMensaje->Size = Drawing::Size(900, 44);
			lblMensaje->BackColor = Color::FromArgb(190, 24, 18, 17);
			lblMensaje->ForeColor = Color::WhiteSmoke;
			lblMensaje->Font = gcnew Drawing::Font(L"Arial", 10, FontStyle::Bold);
			lblMensaje->TextAlign = ContentAlignment::MiddleLeft;
			lblMensaje->Padding = System::Windows::Forms::Padding(12, 0, 8, 0);
			lblMensaje->Text = L"Objetivo: visita el apartamento de Aliona y luego llega a las escaleras. Pulsa E.";

			pnlInfo->Controls->Add(lblNombre);
			pnlInfo->Controls->Add(lblTituloMision);
			pnlInfo->Controls->Add(lblMision);
			pnlInfo->Controls->Add(lblTituloInventario);
			pnlInfo->Controls->Add(lblLlave);
			pnlInfo->Controls->Add(btnPausar);

			this->Controls->Add(pnlEscenario);
			this->Controls->Add(pnlInfo);
			pnlEscenario->Controls->Add(lblMensaje);

			timerPasillo = gcnew System::Windows::Forms::Timer();
			CrearPanelDialogo();
		}

		void CrearPanelDialogo()
		{
			pnlDialogo = gcnew Panel();
			pnlDialogo->Dock = DockStyle::Fill;
			pnlDialogo->BackColor = Color::FromArgb(245, 0, 0, 0);
			pnlDialogo->Visible = false;

			lblTituloDialogo = gcnew Label();
			lblTituloDialogo->AutoSize = false;
			lblTituloDialogo->ForeColor = Color::FromArgb(190, 155, 125);
			lblTituloDialogo->BackColor = Color::Transparent;
			lblTituloDialogo->Font = gcnew Drawing::Font(L"Georgia", 16, FontStyle::Bold);
			lblTituloDialogo->TextAlign = ContentAlignment::MiddleCenter;

			lblTextoDialogo = gcnew Label();
			lblTextoDialogo->AutoSize = false;
			lblTextoDialogo->ForeColor = Color::Gainsboro;
			lblTextoDialogo->BackColor = Color::Transparent;
			lblTextoDialogo->Font = gcnew Drawing::Font(L"Georgia", 16, FontStyle::Regular);
			lblTextoDialogo->TextAlign = ContentAlignment::MiddleLeft;

			lblInstruccionDialogo = gcnew Label();
			lblInstruccionDialogo->AutoSize = false;
			lblInstruccionDialogo->ForeColor = Color::FromArgb(155, 155, 155);
			lblInstruccionDialogo->BackColor = Color::Transparent;
			lblInstruccionDialogo->Font = gcnew Drawing::Font(L"Arial", 10, FontStyle::Regular);
			lblInstruccionDialogo->TextAlign = ContentAlignment::MiddleRight;

			pnlDialogo->Controls->Add(lblTituloDialogo);
			pnlDialogo->Controls->Add(lblTextoDialogo);
			pnlDialogo->Controls->Add(lblInstruccionDialogo);
			pnlEscenario->Controls->Add(pnlDialogo);
			pnlDialogo->BringToFront();

			pnlDialogo->Click += gcnew EventHandler(this, &FrmPasillo::AvanzarDialogoClick);
			lblTituloDialogo->Click += gcnew EventHandler(this, &FrmPasillo::AvanzarDialogoClick);
			lblTextoDialogo->Click += gcnew EventHandler(this, &FrmPasillo::AvanzarDialogoClick);
			lblInstruccionDialogo->Click += gcnew EventHandler(this, &FrmPasillo::AvanzarDialogoClick);
			pnlDialogo->Resize += gcnew EventHandler(this, &FrmPasillo::AcomodarDialogo);
		}

		void CargarSprites()
		{
			try
			{
				String^ ruta = Application::StartupPath + L"\\raskonikov caminando (1).png";
				if (!System::IO::File::Exists(ruta))
					ruta = Application::StartupPath + L"\\raskolnikov_sprites.png";
				hojaSprites = gcnew Bitmap(ruta);
			}
			catch (Exception^)
			{
				hojaSprites = nullptr;
				MessageBox::Show(
					L"No se encontró el spritesheet. Coloca 'raskonikov caminando (1).png' "
					L"o 'raskolnikov_sprites.png' junto al archivo ejecutable.",
					L"Falta el spritesheet",
					MessageBoxButtons::OK,
					MessageBoxIcon::Warning
				);
			}
		}

		void ActualizarZonas()
		{
			int ancho = pnlEscenario->ClientSize.Width;
			int alto = pnlEscenario->ClientSize.Height;
			if (ancho <= 0 || alto <= 0) return;

			zonaPuertaIzquierda = Rectangle(55, static_cast<int>(alto * 0.48), 150, 175);
			zonaPuertaDerecha = Rectangle(ancho - 205, static_cast<int>(alto * 0.48), 150, 175);
			zonaEscaleras = Rectangle(ancho / 2 - 105, static_cast<int>(alto * 0.20), 210, 190);

			if (personajeX == 0 && personajeY == 0)
			{
				personajeX = ancho / 2 - 55;
				personajeY = alto - 230;
			}
		}

		void ActualizarInterfaz()
		{
			lblLlave->Text = llaveObtenida ? L"◆  LLAVE ANTIGUA" : L"◆  SIN LLAVE";
			lblLlave->ForeColor = llaveObtenida ? Color::FromArgb(231, 188, 91) : Color::Silver;
		}

		// Comprueba la proximidad usando el cuerpo completo del personaje.
		// El margen hace que pulsar E junto a una puerta resulte fiable.
		bool EstaCercaDe(Rectangle zona)
		{
			Rectangle cuerpo(personajeX + 20, personajeY + 20, 110, 160);
			cuerpo.Inflate(55, 55);
			return cuerpo.IntersectsWith(zona);
		}

		void AcomodarMensaje()
		{
			if (lblMensaje == nullptr || pnlEscenario == nullptr) return;
			lblMensaje->Width = Math::Max(300, pnlEscenario->ClientSize.Width - 70);
			lblMensaje->Top = Math::Max(12, pnlEscenario->ClientSize.Height - 62);
		}

		void AcomodarDialogo(Object^ sender, EventArgs^ e)
		{
			if (pnlDialogo == nullptr) return;
			int ancho = pnlDialogo->ClientSize.Width;
			int alto = pnlDialogo->ClientSize.Height;
			int margen = Math::Max(35, ancho / 18);
			int anchoContenido = Math::Max(300, ancho - margen * 2);

			lblTituloDialogo->Location = Point(margen, Math::Max(35, alto / 2 - 230));
			lblTituloDialogo->Size = Drawing::Size(anchoContenido, 65);
			lblTextoDialogo->Location = Point(margen + 20, alto / 2 - 125);
			lblTextoDialogo->Size = Drawing::Size(anchoContenido - 40, 185);
			lblInstruccionDialogo->Location = Point(margen, alto / 2 + 75);
			lblInstruccionDialogo->Size = Drawing::Size(anchoContenido, 45);
		}

		void MostrarDialogo(array<String^>^ lineas, String^ titulo, bool cerrarAlFinalizar)
		{
			if (lineas == nullptr || lineas->Length == 0) return;
			timerPasillo->Stop();
			arriba = abajo = izquierda = derecha = false;
			textosDialogo = lineas;
			tituloActual = titulo;
			indiceDialogo = 0;
			cerrarAlTerminar = cerrarAlFinalizar;
			dialogoActivo = true;
			pnlDialogo->Visible = true;
			pnlDialogo->BringToFront();
			AcomodarDialogo(nullptr, nullptr);
			ActualizarTextoDialogo();
		}

		void ActualizarTextoDialogo()
		{
			if (textosDialogo == nullptr || indiceDialogo < 0 || indiceDialogo >= textosDialogo->Length)
				return;
			lblTituloDialogo->Text = tituloActual;
			lblTextoDialogo->Text = textosDialogo[indiceDialogo];
			lblInstruccionDialogo->Text = L"ENTER / ESPACIO / CLIC     " +
				(indiceDialogo + 1).ToString() + L" / " + textosDialogo->Length.ToString();
		}

		void AvanzarDialogo()
		{
			if (!dialogoActivo) return;
			indiceDialogo++;
			if (indiceDialogo < textosDialogo->Length)
			{
				ActualizarTextoDialogo();
				return;
			}

			dialogoActivo = false;
			pnlDialogo->Visible = false;
			if (cerrarAlTerminar)
			{
				this->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->Close();
			}
			else if (!pausado)
			{
				timerPasillo->Start();
				this->Activate();
				this->Focus();
			}
		}

		void AvanzarDialogoClick(Object^ sender, EventArgs^ e)
		{
			AvanzarDialogo();
		}

		void DibujarPuerta(Graphics^ g, Rectangle r, String^ texto)
		{
			SolidBrush^ madera = gcnew SolidBrush(Color::FromArgb(67, 40, 30));
			SolidBrush^ sombra = gcnew SolidBrush(Color::FromArgb(30, 20, 18));
			Pen^ borde = gcnew Pen(Color::FromArgb(132, 91, 61), 4);
			g->FillRectangle(sombra, r.X - 5, r.Y + 5, r.Width + 10, r.Height);
			g->FillRectangle(madera, r);
			g->DrawRectangle(borde, r);
			g->DrawRectangle(Pens::SaddleBrown, r.X + 12, r.Y + 12, r.Width - 24, r.Height / 2 - 18);
			g->DrawRectangle(Pens::SaddleBrown, r.X + 12, r.Y + r.Height / 2, r.Width - 24, r.Height / 2 - 12);
			g->FillEllipse(Brushes::Goldenrod, r.Right - 20, r.Y + r.Height / 2, 7, 7);
			Drawing::Font^ fuente = gcnew Drawing::Font(L"Arial", 8, FontStyle::Bold);
			g->DrawString(texto, fuente, Brushes::Gainsboro, r.X - 5, r.Y - 23);
			delete fuente;
			delete borde;
			delete sombra;
			delete madera;
		}

		void DibujarPersonaje(Graphics^ g, Rectangle destino)
		{
			if (hojaSprites == nullptr)
			{
				SolidBrush^ b = gcnew SolidBrush(Color::SaddleBrown);
				g->FillEllipse(b, destino);
				Drawing::Font^ fuenteFallback = gcnew Drawing::Font(L"Arial", 18, FontStyle::Bold);
				g->DrawString(L"R", fuenteFallback, Brushes::White, destino.X + 38, destino.Y + 45);
				delete fuenteFallback;
				delete b;
				return;
			}

			int anchoCelda = hojaSprites->Width / 4;
			int altoCelda = hojaSprites->Height / 4;
			if (anchoCelda <= 0 || altoCelda <= 0) return;

			filaSprite = Math::Max(0, Math::Min(filaSprite, 3));
			columnaSprite = Math::Max(0, Math::Min(columnaSprite, 3));
			Rectangle origen(columnaSprite * anchoCelda, filaSprite * altoCelda, anchoCelda, altoCelda);
			g->InterpolationMode = Drawing2D::InterpolationMode::NearestNeighbor;
			g->PixelOffsetMode = Drawing2D::PixelOffsetMode::Half;
			g->DrawImage(hojaSprites, destino, origen, GraphicsUnit::Pixel);
		}

		void DibujarEscenario(Graphics^ g)
		{
			int ancho = pnlEscenario->ClientSize.Width;
			int alto = pnlEscenario->ClientSize.Height;
			if (ancho <= 0 || alto <= 0) return;

			g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			g->Clear(Color::FromArgb(33, 27, 26));

			int puntoX = ancho / 2;
			int puntoY = static_cast<int>(alto * 0.38);

			SolidBrush^ pared = gcnew SolidBrush(Color::FromArgb(73, 57, 51));
			SolidBrush^ techo = gcnew SolidBrush(Color::FromArgb(35, 29, 28));
			SolidBrush^ piso = gcnew SolidBrush(Color::FromArgb(87, 62, 48));

			array<Point>^ poligonoTecho = gcnew array<Point>
			{
				Point(0, 0), Point(ancho, 0), Point(puntoX, puntoY), Point(0, puntoY)
			};
			array<Point>^ paredIzq = gcnew array<Point>
			{
				Point(0, 0), Point(puntoX, puntoY), Point(puntoX, alto), Point(0, alto)
			};
			array<Point>^ paredDer = gcnew array<Point>
			{
				Point(ancho, 0), Point(ancho, alto), Point(puntoX, alto), Point(puntoX, puntoY)
			};
			array<Point>^ pisoPerspectiva = gcnew array<Point>
			{
				Point(puntoX, puntoY), Point(ancho, alto), Point(0, alto)
			};

			g->FillPolygon(techo, poligonoTecho);
			g->FillPolygon(pared, paredIzq);
			g->FillPolygon(pared, paredDer);
			g->FillPolygon(piso, pisoPerspectiva);

			Pen^ lineas = gcnew Pen(Color::FromArgb(112, 83, 65), 2);
			g->DrawLine(lineas, puntoX, puntoY, 0, alto);
			g->DrawLine(lineas, puntoX, puntoY, ancho, alto);
			for (int i = 1; i <= 8; i++)
			{
				int y = puntoY + (alto - puntoY) * i / 9;
				g->DrawLine(lineas, 0, y, ancho, y);
			}
			for (int i = -5; i <= 5; i++)
			{
				int xAbajo = puntoX + i * (ancho / 10);
				g->DrawLine(lineas, puntoX, puntoY, xAbajo, alto);
			}
			delete lineas;

			// Molduras y puertas laterales.
			Pen^ moldura = gcnew Pen(Color::FromArgb(107, 76, 57), 9);
			g->DrawLine(moldura, 8, 0, puntoX, puntoY);
			g->DrawLine(moldura, ancho - 8, 0, puntoX, puntoY);
			delete moldura;

			DibujarPuerta(g, zonaPuertaIzquierda, L"PUERTA 01");
			DibujarPuerta(g, zonaPuertaDerecha, L"PUERTA 02");

			// Puerta de salida hacia las escaleras, al fondo del pasillo.
			Rectangle salida(ancho / 2 - 62, static_cast<int>(alto * 0.20), 124, 175);
			DibujarPuerta(g, salida, L"ESCALERAS");
			Drawing::Font^ fuenteSalida = gcnew Drawing::Font(L"Arial", 9, FontStyle::Bold);
			g->DrawString(L"SALIDA", fuenteSalida, Brushes::WhiteSmoke, salida.X + 39, salida.Y + 13);
			delete fuenteSalida;

			// Lámparas tenues en el techo.
			SolidBrush^ luz = gcnew SolidBrush(Color::FromArgb(180, 194, 150, 91));
			g->FillEllipse(luz, puntoX - 15, 35, 30, 12);
			g->FillEllipse(luz, puntoX - 10, static_cast<int>(alto * 0.16), 20, 8);
			delete luz;

			Drawing::Font^ fuente = gcnew Drawing::Font(L"Arial", 10, FontStyle::Bold);
			g->DrawString(L"WASD / FLECHAS: MOVER     E: INTERACTUAR", fuente,
				Brushes::WhiteSmoke, 28, 22);
			delete fuente;

			DibujarPersonaje(g, Rectangle(personajeX, personajeY, 260, 310));

			delete piso;
			delete techo;
			delete pared;
		}

		void Interactuar()
		{
			if (dialogoActivo || pausado) return;

			// PUERTA 01: apartamento de Aliona.
			if (EstaCercaDe(zonaPuertaIzquierda))
			{
				if (cuartoAlionaVisitado)
				{
					MostrarMensaje(L"El apartamento está en silencio. Ya has visitado esta habitación.");
					return;
				}

				timerPasillo->Stop();
				arriba = abajo = izquierda = derecha = false;

				FrmCuartoAliona^ cuarto = gcnew FrmCuartoAliona();
				System::Windows::Forms::DialogResult resultado = cuarto->ShowDialog(this);
				delete cuarto;

				if (resultado == System::Windows::Forms::DialogResult::OK)
				{
					cuartoAlionaVisitado = true;
					lblMision->Text =
						L"[X] Sal de la habitación\r\n"
						L"[X] Visita a Aliona\r\n"
						L"[ ] Llega a las escaleras";
					MostrarMensaje(L"El apartamento queda atrás. Ahora debo llegar a las escaleras.");
				}
				else
				{
					MostrarMensaje(L"La escena no terminó. Puedes volver a entrar por la PUERTA 01.");
				}

				if (!pausado && !this->IsDisposed)
					timerPasillo->Start();

				this->Activate();
				this->Focus();
				pnlEscenario->Invalidate();
				return;
			}

			// PUERTA 02.
			if (EstaCercaDe(zonaPuertaDerecha))
			{
				MostrarMensaje(L"La puerta 02 está cerrada. No parece conveniente llamar.");
				return;
			}

			// ESCALERAS: no se permite omitir la visita al apartamento.
			if (EstaCercaDe(zonaEscaleras))
			{
				if (!llaveObtenida)
				{
					MostrarMensaje(L"Necesito la llave de mi habitación antes de salir.");
					return;
				}

				if (!cuartoAlionaVisitado)
				{
					MostrarMensaje(L"Antes de salir debo entrar en el apartamento de Aliona.");
					return;
				}

				lblMision->Text =
					L"[X] Sal de la habitación\r\n"
					L"[X] Visita a Aliona\r\n"
					L"[X] Llega a las escaleras";

				MostrarDialogo(
					gcnew array<String^>
				{
					L"El aire de las escaleras es frío. La luz del exterior apenas llega hasta aquí.",
						L"Me detengo un instante. Lo ocurrido en el apartamento sigue presente en mi mente.",
						L"No puedo quedarme aquí. Tengo que abandonar el edificio."
				},
					L"CAPÍTULO I — HACIA LA CALLE",
					true
				);
				return;
			}

			MostrarMensaje(L"Acércate a una puerta o a las escaleras y pulsa E para interactuar.");
		}
		void MostrarMensaje(String^ texto)
		{
			lblMensaje->Text = texto;
			lblMensaje->BringToFront();
		}

		System::Void pnlEscenario_Paint(Object^ sender, PaintEventArgs^ e)
		{
			DibujarEscenario(e->Graphics);
		}

		System::Void FrmPasillo_Shown(Object^ sender, EventArgs^ e)
		{
			ActualizarZonas();
			AcomodarMensaje();
			if (dialogoActivo) AcomodarDialogo(nullptr, nullptr);
			pnlEscenario->Invalidate();
			this->Activate();
			this->Focus();
		}

		System::Void FrmPasillo_Resize(Object^ sender, EventArgs^ e)
		{
			if (pnlEscenario == nullptr) return;
			ActualizarZonas();
			AcomodarMensaje();
			pnlEscenario->Invalidate();
		}

		System::Void FrmPasillo_Deactivate(Object^ sender, EventArgs^ e)
		{
			arriba = abajo = izquierda = derecha = false;
		}

		System::Void FrmPasillo_KeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (dialogoActivo)
			{
				if (e->KeyCode == Keys::Enter || e->KeyCode == Keys::Space)
				{
					AvanzarDialogo();
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

		System::Void FrmPasillo_KeyUp(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::W || e->KeyCode == Keys::Up) arriba = false;
			if (e->KeyCode == Keys::S || e->KeyCode == Keys::Down) abajo = false;
			if (e->KeyCode == Keys::A || e->KeyCode == Keys::Left) izquierda = false;
			if (e->KeyCode == Keys::D || e->KeyCode == Keys::Right) derecha = false;
		}

		System::Void timerPasillo_Tick(Object^ sender, EventArgs^ e)
		{
			if (pausado || dialogoActivo) return;

			moviendo = false;
			// A / izquierda siempre resta X; D / derecha siempre suma X.
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

			if (!moviendo) return;

			int ancho = pnlEscenario->ClientSize.Width;
			int alto = pnlEscenario->ClientSize.Height;
			personajeX = Math::Max(18, Math::Min(personajeX, Math::Max(18, ancho - 168)));
			personajeY = Math::Max(18, Math::Min(personajeY, Math::Max(18, alto - 213)));
			columnaSprite = (columnaSprite + 1) % 4;
			pnlEscenario->Invalidate();
		}

		System::Void btnPausar_Click(Object^ sender, EventArgs^ e)
		{
			if (dialogoActivo) return;
			pausado = !pausado;
			btnPausar->Text = pausado ? L"CONTINUAR" : L"PAUSAR";
			if (pausado)
			{
				timerPasillo->Stop();
				arriba = abajo = izquierda = derecha = false;
			}
			else
			{
				timerPasillo->Start();
				this->Activate();
				this->Focus();
			}
		}
	private: System::Void InitializeComponent() {
		this->SuspendLayout();
		// 
		// FrmPasillo
		// 
		this->ClientSize = System::Drawing::Size(1207, 537);
		this->Name = L"FrmPasillo";
		this->ResumeLayout(false);
	}
	};
}
