#pragma once
#include "FrmMinijuegos.h"

namespace CrimenYCastigo2 {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class PanelDobleBufferAliona : public Panel
	{
	public:
		PanelDobleBufferAliona()
		{
			this->DoubleBuffered = true;
			this->ResizeRedraw = true;
			this->SetStyle(
				ControlStyles::AllPaintingInWmPaint |
				ControlStyles::UserPaint |
				ControlStyles::OptimizedDoubleBuffer,
				true);
			this->UpdateStyles();
		}
	};

	public ref class FrmCuartoAliona : public Form
	{
	private:
		PanelDobleBufferAliona^ pnlEscena;
		Timer^ timerEscena;

		Bitmap^ hojaAliona;
		Bitmap^ hojaLizabeta;
		Bitmap^ hojaRaskolnikov;
		Bitmap^ hojaHacha;

		int fase;
		int contador;
		int alionaX;
		int raskX;
		int lizabetaX;
		int alphaOscuridad;
		int indiceDialogo;
		int continuarDespues;
		int cordura;

		bool puertaAbierta;
		bool alionaVisible;
		bool lizabetaVisible;
		bool dialogoActivo;
		bool secuenciaTerminada;
		bool mostrandoGolpes;

		array<String^>^ dialogos;
		array<String^>^ emisores;
		String^ emisorActual;
		String^ textoActual;

	public:
		FrmCuartoAliona()
		{
			InitializeInterfaz();

			hojaAliona = nullptr;
			hojaLizabeta = nullptr;
			hojaRaskolnikov = nullptr;
			hojaHacha = nullptr;

			fase = 0;
			contador = 0;
			alionaX = 0;
			raskX = 0;
			lizabetaX = 0;
			alphaOscuridad = 0;
			indiceDialogo = 0;
			continuarDespues = 0;
			cordura = 100;

			puertaAbierta = false;
			alionaVisible = true;
			lizabetaVisible = false;
			dialogoActivo = false;
			secuenciaTerminada = false;
			mostrandoGolpes = true;

			dialogos = nullptr;
			emisores = nullptr;
			emisorActual = L"";
			textoActual = L"";

			this->Text = L"Crimen y castigo — Apartamento de Aliona";
			this->BackColor = Color::FromArgb(24, 19, 18);
			this->KeyPreview = true;
			this->DoubleBuffered = true;
			this->WindowState = FormWindowState::Maximized;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->MinimizeBox = false;

			CargarSprites();

			timerEscena->Interval = 100;
			timerEscena->Tick += gcnew EventHandler(this, &FrmCuartoAliona::timerEscena_Tick);
			pnlEscena->Paint += gcnew PaintEventHandler(this, &FrmCuartoAliona::pnlEscena_Paint);
			pnlEscena->Click += gcnew EventHandler(this, &FrmCuartoAliona::pnlEscena_Click);
			this->KeyDown += gcnew KeyEventHandler(this, &FrmCuartoAliona::FrmCuartoAliona_KeyDown);
			this->Shown += gcnew EventHandler(this, &FrmCuartoAliona::FrmCuartoAliona_Shown);
			this->Resize += gcnew EventHandler(this, &FrmCuartoAliona::FrmCuartoAliona_Resize);
		}

		property int CorduraFinal
		{
			int get() { return cordura; }
		}

	protected:
		~FrmCuartoAliona()
		{
			if (timerEscena != nullptr)
				timerEscena->Stop();

			if (hojaAliona != nullptr) { delete hojaAliona; hojaAliona = nullptr; }
			if (hojaLizabeta != nullptr) { delete hojaLizabeta; hojaLizabeta = nullptr; }
			if (hojaRaskolnikov != nullptr) { delete hojaRaskolnikov; hojaRaskolnikov = nullptr; }
			if (hojaHacha != nullptr) { delete hojaHacha; hojaHacha = nullptr; }
		}

	private:
		void InitializeInterfaz()
		{
			pnlEscena = gcnew PanelDobleBufferAliona();
			pnlEscena->Dock = DockStyle::Fill;
			pnlEscena->BackColor = Color::FromArgb(35, 27, 24);
			pnlEscena->TabStop = false;
			this->Controls->Add(pnlEscena);

			timerEscena = gcnew Timer();
		}

		Bitmap^ CargarImagen(String^ nombre)
		{
			String^ carpetaBase = Application::StartupPath;
			String^ carpetaAssets = System::IO::Path::Combine(carpetaBase, L"Assets");
			String^ carpetaActual = Environment::CurrentDirectory;
			String^ carpetaActualAssets = System::IO::Path::Combine(carpetaActual, L"Assets");
			array<String^>^ carpetas = gcnew array<String^>
			{
				carpetaBase,
					carpetaAssets,
					carpetaActual,
					carpetaActualAssets
			};

			for each (String ^ carpeta in carpetas)
			{
				try
				{
					String^ ruta = System::IO::Path::Combine(carpeta, nombre);
					if (System::IO::File::Exists(ruta))
						return gcnew Bitmap(ruta);
				}
				catch (Exception^) {}
			}
			return nullptr;
		}

		void CargarSprites()
		{
			hojaAliona = CargarImagen(L"Aliona Sprites.png");
			hojaLizabeta = CargarImagen(L"Lizabeta wip Sprites.png");
			hojaHacha = CargarImagen(L"Hacha.png");

			hojaRaskolnikov = CargarImagen(L"raskonikov caminando (1).png");
			if (hojaRaskolnikov == nullptr)
				hojaRaskolnikov = CargarImagen(L"raskolnikov_sprites.png");
		}

		void PrepararPosiciones()
		{
			int ancho = Math::Max(1, pnlEscena->ClientSize.Width);
			alionaX = static_cast<int>(ancho * 0.66);
			raskX = static_cast<int>(ancho * 0.06);
			lizabetaX = ancho + 80;
		}

		void IniciarDialogoInicial()
		{
			MostrarGuion(
				gcnew array<String^>
			{
				L"¿Quién llama? ¿Qué desea a estas horas?",
					L"Vengo por el objeto que le mencioné. Quisiera empeñarlo.",
					L"Pase. Enséñemelo; veamos qué ha traído."
			},
				gcnew array<String^>
			{
				L"ALIONA",
					L"RASKÓLNIKOV",
					L"ALIONA"
			},
				1
			);
		}

		void IniciarDialogoRevision()
		{
			MostrarGuion(
				gcnew array<String^>
			{
				L"Déjeme examinarlo con cuidado...",
					L"Aliona se inclina sobre la mesa para revisar el objeto. Raskólnikov espera, tenso.",
					L"Por un instante, ella deja de prestarle atención. Él cree que ha llegado el momento."
			},
				gcnew array<String^>
			{
				L"ALIONA",
					L"NARRADOR",
					L"NARRADOR"
			},
				2
			);
		}

		void IniciarDialogoLizabeta()
		{
			MostrarGuion(
				gcnew array<String^>
			{
				L"¿Hermana...? ¿Qué ha ocurrido aquí?",
					L"Lizaveta ha regresado inesperadamente. Se detiene al entrar y ve a Raskólnikov.",
					L"Raskólnikov comprende que la situación ha cambiado y que ya no puede volver atrás."
			},
				gcnew array<String^>
			{
				L"LIZAVETA",
					L"NARRADOR",
					L"NARRADOR"
			},
				4
			);
		}

		void IniciarDialogoFinal()
		{
			MostrarGuion(
				gcnew array<String^>
			{
				L"La escena se funde en la oscuridad. El silencio del apartamento pesa sobre Raskólnikov.",
					L"Todo ha terminado... pero él no consigue apartar de su mente lo que acaba de ocurrir."
			},
				gcnew array<String^>
			{
				L"NARRADOR",
					L"RASKÓLNIKOV"
			},
				5
			);
		}

		void IniciarDialogoReflexion()
		{
			MostrarGuion(
				gcnew array<String^>
			{
				L"¿Qué he hecho...? No era así como debía sentirse.",
					L"Pensé que podría controlar cada detalle, pero ahora no puedo dejar de pensar en lo ocurrido.",
					L"El silencio de esta habitación me atormenta. Cada pequeño ruido parece anunciar que alguien viene.",
					L"Tengo que respirar. Debo recuperar el control de mis pensamientos.",
					L"No puedo quedarme paralizado. Necesito ordenar mi mente antes de abandonar este lugar."
			},
				gcnew array<String^>
			{
				L"RASKÓLNIKOV",
					L"RASKÓLNIKOV",
					L"RASKÓLNIKOV",
					L"RASKÓLNIKOV",
					L"RASKÓLNIKOV"
			},
				6
			);
		}

		void IniciarDialogoCierre()
		{
			String^ lineaCordura = L"CORDURA FINAL: " + cordura.ToString() + L" / 100.";
			MostrarGuion(
				gcnew array<String^>
			{
				L"Raskólnikov consigue recuperar parcialmente el control de sí mismo.",
					L"Pero sabe que no puede permanecer mucho más tiempo en el apartamento.",
					lineaCordura,
					L"Debo salir de aquí..."
			},
				gcnew array<String^>
			{
				L"NARRADOR",
					L"RASKÓLNIKOV",
					L"SISTEMA",
					L"RASKÓLNIKOV"
			},
				7
			);
		}

		void MostrarGuion(array<String^>^ lineas, array<String^>^ nombres, int siguiente)
		{
			if (lineas == nullptr || nombres == nullptr || lineas->Length == 0 || lineas->Length != nombres->Length)
				return;

			dialogos = lineas;
			emisores = nombres;
			indiceDialogo = 0;
			continuarDespues = siguiente;
			dialogoActivo = true;
			ActualizarDialogo();
			timerEscena->Stop();
			pnlEscena->Invalidate();
		}

		void ActualizarDialogo()
		{
			if (dialogos == nullptr || emisores == nullptr || indiceDialogo < 0 || indiceDialogo >= dialogos->Length)
				return;

			emisorActual = emisores[indiceDialogo];
			textoActual = dialogos[indiceDialogo];
		}

		void AvanzarDialogo()
		{
			if (!dialogoActivo)
				return;

			indiceDialogo++;
			if (indiceDialogo < dialogos->Length)
			{
				ActualizarDialogo();
				pnlEscena->Invalidate();
				return;
			}

			dialogoActivo = false;
			int siguiente = continuarDespues;
			continuarDespues = 0;

			switch (siguiente)
			{
			case 1:
				IniciarDialogoRevision();
				break;

			case 2:
				fase = 2;
				contador = 0;
				alphaOscuridad = 0;
				timerEscena->Start();
				break;

			case 4:
				fase = 5;
				contador = 0;
				alphaOscuridad = 0;
				timerEscena->Start();
				break;

			case 5:
		
				IniciarDialogoReflexion();
				break;

			case 6:
		
				IniciarSecuenciaMinijuegos();
				break;

			case 7:

				secuenciaTerminada = true;
				this->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->Close();
				break;
			}
		}

		void AjustarCordura(int cantidad)
		{
			cordura = Math::Max(0, Math::Min(100, cordura + cantidad));
		}


		bool JugarRespiracion()
		{
			FrmRespirar^ juego = gcnew FrmRespirar();
			System::Windows::Forms::DialogResult resultado = juego->ShowDialog(this);
			delete juego;
			return resultado == System::Windows::Forms::DialogResult::OK;
		}

		bool JugarConcentracion()
		{
			FrmConcentracion^ juego = gcnew FrmConcentracion();
			System::Windows::Forms::DialogResult resultado = juego->ShowDialog(this);
			delete juego;
			return resultado == System::Windows::Forms::DialogResult::OK;
		}

		bool JugarTemblor()
		{
			FrmTemblor^ juego = gcnew FrmTemblor();
			System::Windows::Forms::DialogResult resultado = juego->ShowDialog(this);
			delete juego;
			return resultado == System::Windows::Forms::DialogResult::OK;
		}

		void MostrarFalloMinijuego(String^ mensaje, String^ titulo)
		{
			MessageBox::Show(
				this,
				mensaje + L" Cordura -5. Vuelve a intentarlo.",
				titulo,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning
			);
		}

		void IniciarSecuenciaMinijuegos()
		{
			
			timerEscena->Stop();

			// MINIJUEGO 1.
			while (!JugarRespiracion())
			{
				AjustarCordura(-5);
				MostrarFalloMinijuego(
					L"No lograste controlar tu respiración.",
					L"Respiración fallida"
				);
			}
			AjustarCordura(10);

			// MINIJUEGO 2
			while (!JugarConcentracion())
			{
				AjustarCordura(-5);
				MostrarFalloMinijuego(
					L"No lograste recordar la secuencia.",
					L"Concentración fallida"
				);
			}
			AjustarCordura(5);

			// MINIJUEGO 3
			while (!JugarTemblor())
			{
				AjustarCordura(-5);
				MostrarFalloMinijuego(
					L"No lograste controlar tus manos.",
					L"Temblor fallido"
				);
			}
			AjustarCordura(5);

			IniciarDialogoCierre();
		}

		void DibujarFondo(Graphics^ g, int ancho, int alto)
		{
			g->Clear(Color::FromArgb(48, 36, 31));

			SolidBrush^ pared = gcnew SolidBrush(Color::FromArgb(91, 68, 56));
			SolidBrush^ paredSombra = gcnew SolidBrush(Color::FromArgb(56, 42, 37));
			SolidBrush^ piso = gcnew SolidBrush(Color::FromArgb(77, 53, 42));
			SolidBrush^ alfombra = gcnew SolidBrush(Color::FromArgb(91, 42, 35));
			SolidBrush^ madera = gcnew SolidBrush(Color::FromArgb(75, 43, 30));
			SolidBrush^ luz = gcnew SolidBrush(Color::FromArgb(70, 218, 167, 99));
			Pen^ borde = gcnew Pen(Color::FromArgb(130, 91, 65), 5);

			g->FillRectangle(pared, 0, 0, ancho, static_cast<int>(alto * 0.77));
			g->FillRectangle(paredSombra, 0, 0, ancho, static_cast<int>(alto * 0.12));
			g->FillRectangle(piso, 0, static_cast<int>(alto * 0.77), ancho, alto);
			g->FillRectangle(alfombra, static_cast<int>(ancho * 0.24), static_cast<int>(alto * 0.78),
				static_cast<int>(ancho * 0.53), static_cast<int>(alto * 0.17));
			g->DrawRectangle(borde, static_cast<int>(ancho * 0.035), static_cast<int>(alto * 0.08),
				ancho - static_cast<int>(ancho * 0.07), static_cast<int>(alto * 0.65));

			// Ventana y cortinas.
			g->FillRectangle(Brushes::DarkSlateGray, static_cast<int>(ancho * 0.73), static_cast<int>(alto * 0.15),
				static_cast<int>(ancho * 0.17), static_cast<int>(alto * 0.26));
			g->DrawRectangle(Pens::DimGray, static_cast<int>(ancho * 0.73), static_cast<int>(alto * 0.15),
				static_cast<int>(ancho * 0.17), static_cast<int>(alto * 0.26));
			g->DrawLine(Pens::Gray, static_cast<int>(ancho * 0.815), static_cast<int>(alto * 0.15),
				static_cast<int>(ancho * 0.815), static_cast<int>(alto * 0.41));
			g->DrawLine(Pens::Gray, static_cast<int>(ancho * 0.73), static_cast<int>(alto * 0.28),
				static_cast<int>(ancho * 0.90), static_cast<int>(alto * 0.28));

			// Puerta de entrada.
			int puertaX = static_cast<int>(ancho * 0.09);
			int puertaY = static_cast<int>(alto * 0.20);
			int puertaW = static_cast<int>(ancho * 0.18);
			int puertaH = static_cast<int>(alto * 0.57);
			g->FillRectangle(Brushes::Black, puertaX - 10, puertaY - 10, puertaW + 20, puertaH + 20);
			g->FillRectangle(madera, puertaX, puertaY, puertaW, puertaH);
			g->DrawRectangle(borde, puertaX, puertaY, puertaW, puertaH);
			if (puertaAbierta)
			{
				Point p1(puertaX + 8, puertaY + 8);
				Point p2(puertaX + puertaW + 45, puertaY + 30);
				Point p3(puertaX + puertaW + 45, puertaY + puertaH - 15);
				Point p4(puertaX + 8, puertaY + puertaH - 8);
				array<Point>^ hoja = gcnew array<Point>{ p1, p2, p3, p4 };
				g->FillPolygon(Brushes::SaddleBrown, hoja);
				g->DrawPolygon(borde, hoja);
			}
			else
			{
				g->DrawRectangle(Pens::SaddleBrown, puertaX + 18, puertaY + 18, puertaW - 36, puertaH / 2 - 25);
				g->FillEllipse(Brushes::Goldenrod, puertaX + puertaW - 28, puertaY + puertaH / 2, 11, 11);
			}

			// Mesa de la prestamista.
			int mesaX = static_cast<int>(ancho * 0.53);
			int mesaY = static_cast<int>(alto * 0.65);
			int mesaW = static_cast<int>(ancho * 0.34);
			int mesaH = static_cast<int>(alto * 0.07);
			g->FillRectangle(madera, mesaX, mesaY, mesaW, mesaH);
			g->FillRectangle(Brushes::SaddleBrown, mesaX + 18, mesaY + mesaH, 18, static_cast<int>(alto * 0.13));
			g->FillRectangle(Brushes::SaddleBrown, mesaX + mesaW - 36, mesaY + mesaH, 18, static_cast<int>(alto * 0.13));
			g->FillEllipse(luz, mesaX + mesaW / 2 - 16, mesaY - 34, 32, 18);

			// Cuadro antiguo.
			g->DrawRectangle(Pens::Sienna, static_cast<int>(ancho * 0.42), static_cast<int>(alto * 0.16),
				static_cast<int>(ancho * 0.12), static_cast<int>(alto * 0.19));
			g->FillRectangle(Brushes::DarkGoldenrod, static_cast<int>(ancho * 0.435), static_cast<int>(alto * 0.18),
				static_cast<int>(ancho * 0.09), static_cast<int>(alto * 0.15));

			delete luz;
			delete madera;
			delete alfombra;
			delete piso;
			delete paredSombra;
			delete pared;
			delete borde;
		}

		Rectangle ObtenerCuadroAliona(int indice)
		{
			switch (indice % 8)
			{
			case 0: return Rectangle(204, 109, 267, 369);
			case 1: return Rectangle(887, 116, 267, 362);
			case 2: return Rectangle(1577, 109, 287, 369);
			case 3: return Rectangle(211, 805, 288, 356);
			case 4: return Rectangle(894, 805, 287, 356);
			case 5: return Rectangle(1577, 805, 287, 356);
			case 6: return Rectangle(880, 1474, 301, 370);
			default: return Rectangle(204, 1481, 295, 363);
			}
		}

		void DibujarAliona(Graphics^ g, int x, int y, int frame)
		{
			Rectangle destino(x, y, 240, 290);
			if (hojaAliona != nullptr)
			{
				Rectangle origen = ObtenerCuadroAliona(frame);
				g->DrawImage(hojaAliona, destino, origen, GraphicsUnit::Pixel);
			}
			else
			{
				Drawing::Font^ aviso = gcnew Drawing::Font(L"Arial", 10, FontStyle::Bold);
				g->DrawString(L"FALTA Aliona Sprites.png", aviso, Brushes::White,
					static_cast<float>(x), static_cast<float>(y + 20));
				delete aviso;
			}
		}

		void DibujarLizabeta(Graphics^ g, int x, int y, int frame)
		{
			Rectangle origen = (frame % 2 == 0)
				? Rectangle(307, 123, 400, 594)
				: Rectangle(307, 1157, 400, 584);
			Rectangle destino(x, y, 145, 215);

			if (hojaLizabeta != nullptr)
				g->DrawImage(hojaLizabeta, destino, origen, GraphicsUnit::Pixel);
			else
			{
				Drawing::Font^ aviso = gcnew Drawing::Font(L"Arial", 10, FontStyle::Bold);
				g->DrawString(L"FALTA Lizabeta wip Sprites.png", aviso, Brushes::White, x, y + 20);
				delete aviso;
			}
		}

		void DibujarRaskolnikov(Graphics^ g, int x, int y)
		{
			if (hojaRaskolnikov != nullptr)
			{
				int celdaW = hojaRaskolnikov->Width / 4;
				int celdaH = hojaRaskolnikov->Height / 4;
				if (celdaW > 0 && celdaH > 0)
				{
					Rectangle origen(0, 0, celdaW, celdaH);
					Rectangle destino(x, y, 400, 590);
					g->DrawImage(hojaRaskolnikov, destino, origen, GraphicsUnit::Pixel);
					return;
				}
			}

			Drawing::Font^ aviso = gcnew Drawing::Font(L"Arial", 9, FontStyle::Bold);
			g->DrawString(L"FALTA SPRITESHEET DE RASKÓLNIKOV", aviso, Brushes::White, x, y + 25);
			delete aviso;
		}

		void DibujarHacha(Graphics^ g)
		{
			if (fase != 2 || contador < 2 || contador > 19 || hojaHacha == nullptr)
				return;

			float angulo;
			if (contador <= 8)
				angulo = -58.0f + contador * 14.5f;
			else
				angulo = 58.0f - (contador - 8) * 6.5f;

			float pivoteX = static_cast<float>(raskX + 118);
			float pivoteY = static_cast<float>(pnlEscena->ClientSize.Height * 0.64);

			Drawing2D::GraphicsState^ estado = g->Save();
			g->TranslateTransform(pivoteX, pivoteY);
			g->RotateTransform(angulo);
			g->ScaleTransform(-1.0f, 1.0f);
			g->InterpolationMode = Drawing2D::InterpolationMode::NearestNeighbor;
			g->PixelOffsetMode = Drawing2D::PixelOffsetMode::Half;
			g->DrawImage(hojaHacha, Rectangle(-28, -165, 56, 165));
			g->Restore(estado);
		}

		void DibujarDialogo(Graphics^ g, int ancho, int alto)
		{
			if (!dialogoActivo)
				return;

			int y = alto - 175;
			SolidBrush^ fondo = gcnew SolidBrush(Color::FromArgb(232, 10, 9, 9));
			SolidBrush^ dorado = gcnew SolidBrush(Color::FromArgb(214, 177, 125));
			SolidBrush^ texto = gcnew SolidBrush(Color::Gainsboro);
			Drawing::Font^ fuenteNombre = gcnew Drawing::Font(L"Georgia", 14, FontStyle::Bold);
			Drawing::Font^ fuenteTexto = gcnew Drawing::Font(L"Georgia", 13, FontStyle::Regular);
			Drawing::Font^ fuenteAyuda = gcnew Drawing::Font(L"Arial", 9, FontStyle::Regular);

			g->FillRectangle(fondo, 0, y, ancho, 175);
			g->DrawString(emisorActual, fuenteNombre, dorado, 45, y + 20);
			RectangleF area(55.0f, y + 52.0f, static_cast<float>(Math::Max(100, ancho - 110)), 82.0f);
			StringFormat^ formato = gcnew StringFormat();
			formato->Alignment = StringAlignment::Near;
			formato->LineAlignment = StringAlignment::Near;
			formato->Trimming = StringTrimming::Word;
			g->DrawString(textoActual, fuenteTexto, texto, area, formato);
			delete formato;
			g->DrawString(L"ENTER / ESPACIO / CLIC PARA CONTINUAR", fuenteAyuda, Brushes::Silver,
				static_cast<float>(ancho - 330), static_cast<float>(alto - 32));

			delete fuenteAyuda;
			delete fuenteTexto;
			delete fuenteNombre;
			delete texto;
			delete dorado;
			delete fondo;
		}

		void DibujarEscena(Graphics^ g)
		{
			int ancho = pnlEscena->ClientSize.Width;
			int alto = pnlEscena->ClientSize.Height;
			if (ancho <= 0 || alto <= 0) return;

			g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			g->InterpolationMode = Drawing2D::InterpolationMode::NearestNeighbor;
			g->PixelOffsetMode = Drawing2D::PixelOffsetMode::Half;

			DibujarFondo(g, ancho, alto);

			int pisoPersonajes = static_cast<int>(alto * 0.79);
			if (alionaVisible)
			{
				int frame = (fase == 1 && indiceDialogo == 0) ? 1 : ((contador / 7) % 2);
				DibujarAliona(g, alionaX, pisoPersonajes - 215, frame);
			}
			DibujarRaskolnikov(g, raskX, pisoPersonajes - 210);

			if (lizabetaVisible)
				DibujarLizabeta(g, lizabetaX, pisoPersonajes - 215, (contador / 8) % 2);

			DibujarHacha(g);

			if (mostrandoGolpes && fase == 0 && contador >= 4)
			{
				Drawing::Font^ fuenteGolpes = gcnew Drawing::Font(L"Georgia", 24, FontStyle::Bold);
				g->DrawString((contador / 4) % 2 == 0 ? L"TOC... TOC..." : L"TOC...     TOC...",
					fuenteGolpes, Brushes::Wheat, static_cast<float>(ancho * 0.30), static_cast<float>(alto * 0.12));
				delete fuenteGolpes;
			}

			if (alphaOscuridad > 0)
			{
				SolidBrush^ sombra = gcnew SolidBrush(Color::FromArgb(
					Math::Max(0, Math::Min(255, alphaOscuridad)), 0, 0, 0));
				g->FillRectangle(sombra, 0, 0, ancho, alto);
				delete sombra;
			}

			DibujarDialogo(g, ancho, alto);
		}

		System::Void pnlEscena_Paint(Object^ sender, PaintEventArgs^ e)
		{
			DibujarEscena(e->Graphics);
		}

		System::Void pnlEscena_Click(Object^ sender, EventArgs^ e)
		{
			AvanzarDialogo();
		}

		System::Void FrmCuartoAliona_KeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (dialogoActivo && (e->KeyCode == Keys::Enter || e->KeyCode == Keys::Space))
			{
				AvanzarDialogo();
				e->SuppressKeyPress = true;
				return;
			}

			if (secuenciaTerminada && e->KeyCode == Keys::Escape)
			{
				this->Close();
				e->SuppressKeyPress = true;
			}
		}

		System::Void FrmCuartoAliona_Shown(Object^ sender, EventArgs^ e)
		{
			PrepararPosiciones();
			contador = 0;
			fase = 0;
			timerEscena->Start();
			pnlEscena->Invalidate();
		}

		System::Void FrmCuartoAliona_Resize(Object^ sender, EventArgs^ e)
		{
			if (pnlEscena != nullptr)
				pnlEscena->Invalidate();
		}

		System::Void timerEscena_Tick(Object^ sender, EventArgs^ e)
		{
			if (dialogoActivo || secuenciaTerminada)
				return;

			contador++;

			if (fase == 0)
			{
				int ancho = pnlEscena->ClientSize.Width;
				if (contador >= 8 && alionaX > static_cast<int>(ancho * 0.31))
					alionaX -= 10;

				if (contador >= 23)
					puertaAbierta = true;

				if (contador >= 26 && raskX < static_cast<int>(ancho * 0.34))
					raskX += 12;

				if (contador >= 48)
				{
					mostrandoGolpes = false;
					IniciarDialogoInicial();
					return;
				}
			}
			else if (fase == 2)
			{
				if (contador >= 9)
					alionaVisible = false;

				if (contador >= 12)
					alphaOscuridad = Math::Min(210, alphaOscuridad + 18);

				if (contador >= 25)
				{
					fase = 3;
					contador = 0;
					alphaOscuridad = 35;
					lizabetaVisible = true;
					lizabetaX = pnlEscena->ClientSize.Width + 80;
				}
			}
			else if (fase == 3)
			{
				int objetivo = static_cast<int>(pnlEscena->ClientSize.Width * 0.70);
				if (lizabetaX > objetivo)
					lizabetaX -= 15;

				if (lizabetaX <= objetivo)
				{
					fase = 4;
					contador = 0;
					alphaOscuridad = 25;
					IniciarDialogoLizabeta();
					return;
				}
			}
			else if (fase == 5)
			{
				alphaOscuridad = Math::Min(245, alphaOscuridad + 12);
				if (alphaOscuridad >= 245)
				{
					fase = 6;
					contador = 0;
					IniciarDialogoFinal();
					return;
				}
			}

			pnlEscena->Invalidate();
		}
	};
}
