#pragma once

namespace CrimenYCastigo2 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class PanelMinijuegoDobleBuffer : public Panel
    {
    public:
        PanelMinijuegoDobleBuffer()
        {
            this->DoubleBuffered = true;
            this->ResizeRedraw = true;
            this->SetStyle(ControlStyles::AllPaintingInWmPaint |
                ControlStyles::UserPaint | ControlStyles::OptimizedDoubleBuffer, true);
            this->UpdateStyles();
        }
    };

    // MINIJUEGO 1
   
    public ref class FrmRespirar : public Form
    {
    private:
        PanelMinijuegoDobleBuffer^ escena;
        Timer^ reloj;
        array<Keys>^ secuencia;
        int paso;
        float fasePulso;
        DateTime limite;
        bool terminado;

    public:
        FrmRespirar()
        {
            secuencia = gcnew array<Keys>{ Keys::A, Keys::A, Keys::W, Keys::D, Keys::S };
            paso = 0;
            fasePulso = 0.0f;
            limite = DateTime::Now.AddMilliseconds(1500);
            terminado = false;

            this->Text = L"La respiración — Crimen y castigo";
            this->ClientSize = Drawing::Size(760, 500);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->KeyPreview = true;
            this->BackColor = Color::FromArgb(15, 25, 31);

            escena = gcnew PanelMinijuegoDobleBuffer();
            escena->Dock = DockStyle::Fill;
            escena->BackColor = this->BackColor;
            escena->Paint += gcnew PaintEventHandler(this, &FrmRespirar::Escena_Paint);
            this->Controls->Add(escena);

            reloj = gcnew Timer();
            reloj->Interval = 25;
            reloj->Tick += gcnew EventHandler(this, &FrmRespirar::Reloj_Tick);
            this->KeyDown += gcnew KeyEventHandler(this, &FrmRespirar::Frm_KeyDown);
            this->Shown += gcnew EventHandler(this, &FrmRespirar::Frm_Shown);
        }

    public:
        ~FrmRespirar()
        {
            if (reloj != nullptr) { reloj->Stop(); delete reloj; reloj = nullptr; }
        }

    private:
        void Finalizar(bool exito)
        {
            if (terminado) return;
            terminado = true;
            reloj->Stop();
            this->DialogResult = exito ? System::Windows::Forms::DialogResult::OK : System::Windows::Forms::DialogResult::Retry;
            this->Close();
        }

        System::Void Frm_Shown(Object^ sender, EventArgs^ e)
        {
            limite = DateTime::Now.AddMilliseconds(1500);
            reloj->Start();
            this->Focus();
        }

        System::Void Reloj_Tick(Object^ sender, EventArgs^ e)
        {
            fasePulso += 0.11f;
            if (DateTime::Now >= limite) { Finalizar(false); return; }
            escena->Invalidate();
        }

        System::Void Frm_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (terminado) return;
            if (e->KeyCode != Keys::A && e->KeyCode != Keys::W &&
                e->KeyCode != Keys::D && e->KeyCode != Keys::S) return;

            if (e->KeyCode != secuencia[paso]) Finalizar(false);
            else
            {
                ++paso;
                if (paso >= secuencia->Length) Finalizar(true);
                else limite = DateTime::Now.AddMilliseconds(1500);
            }
            e->SuppressKeyPress = true;
            escena->Invalidate();
        }

        System::Void Escena_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            g->SmoothingMode = SmoothingMode::AntiAlias;
            int w = escena->ClientSize.Width;
            int h = escena->ClientSize.Height;
            g->Clear(Color::FromArgb(15, 25, 31));

            SolidBrush^ blanco = gcnew SolidBrush(Color::FromArgb(235, 239, 232));
            SolidBrush^ tenue = gcnew SolidBrush(Color::FromArgb(155, 177, 180));
            SolidBrush^ acento = gcnew SolidBrush(Color::FromArgb(102, 190, 169));
            SolidBrush^ oscuro = gcnew SolidBrush(Color::FromArgb(31, 47, 53));
            Pen^ linea = gcnew Pen(Color::FromArgb(82, 132, 133), 2);
            Drawing::Font^ titulo = gcnew Drawing::Font(L"Georgia", 23, FontStyle::Bold);
            Drawing::Font^ normal = gcnew Drawing::Font(L"Segoe UI", 12, FontStyle::Regular);
            Drawing::Font^ grande = gcnew Drawing::Font(L"Georgia", 27, FontStyle::Bold);

            g->DrawString(L"RECUPERA EL ALIENTO", titulo, blanco, 38, 28);
            g->DrawString(L"Sigue el ritmo. No dejes que el pánico te domine.", normal, tenue, 41, 78);

            float onda = 0.5f + 0.5f * static_cast<float>(Math::Sin(fasePulso));
            int diametro = 105 + static_cast<int>(onda * 35);
            int cx = w / 2;
            int cy = 230;
            g->FillEllipse(oscuro, cx - 95, cy - 95, 190, 190);
            g->FillEllipse(acento, cx - diametro / 2, cy - diametro / 2, diametro, diametro);
            g->DrawEllipse(linea, cx - 102, cy - 102, 204, 204);
            g->DrawString(L"INHALA", grande, blanco, cx - 66, cy - 19);

            for (int i = 0; i < 5; ++i)
            {
                int x = 205 + i * 74;
                SolidBrush^ b = gcnew SolidBrush(i < paso ? Color::FromArgb(102, 190, 169) : Color::FromArgb(53, 72, 78));
                g->FillEllipse(b, x, 365, 42, 42);
                g->DrawString((i + 1).ToString(), normal, i < paso ? Brushes::Black : blanco, x + 14, 374);
                delete b;
            }

            double ms = Math::Max(0.0, (limite - DateTime::Now).TotalMilliseconds);
            float fraccion = static_cast<float>(Math::Min(1.0, ms / 1500.0));
            g->FillRectangle(oscuro, 40, 438, w - 80, 13);
            g->FillRectangle(acento, 40, 438, static_cast<int>((w - 80) * fraccion), 13);
            g->DrawString(L"Pulsa: A  ·  A  ·  W  ·  D  ·  S", normal, blanco, 40, 466);

            delete grande; delete normal; delete titulo; delete linea;
            delete oscuro; delete acento; delete tenue; delete blanco;
        }
    };

    // MINIJUEGO 2: CONCENTRACIÓN

    public ref class FrmConcentracion : public Form
    {
    private:
        PanelMinijuegoDobleBuffer^ escena;
        Timer^ reloj;
        DateTime limiteMemoria;
        bool mostrando;
        bool terminado;
        int entrada;
        array<String^>^ simbolos;

    public:
        FrmConcentracion()
        {
            simbolos = gcnew array<String^>{ L"1", L"2", L"3", L"4", L"5" };
            limiteMemoria = DateTime::Now.AddSeconds(2);
            mostrando = true;
            terminado = false;
            entrada = 0;

            this->Text = L"Concentración — Crimen y castigo";
            this->ClientSize = Drawing::Size(760, 500);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->KeyPreview = true;
            this->BackColor = Color::FromArgb(22, 22, 35);

            escena = gcnew PanelMinijuegoDobleBuffer();
            escena->Dock = DockStyle::Fill;
            escena->BackColor = this->BackColor;
            escena->Paint += gcnew PaintEventHandler(this, &FrmConcentracion::Escena_Paint);
            this->Controls->Add(escena);

            reloj = gcnew Timer();
            reloj->Interval = 30;
            reloj->Tick += gcnew EventHandler(this, &FrmConcentracion::Reloj_Tick);
            this->KeyDown += gcnew KeyEventHandler(this, &FrmConcentracion::Frm_KeyDown);
            this->Shown += gcnew EventHandler(this, &FrmConcentracion::Frm_Shown);
        }

    public:
        ~FrmConcentracion()
        {
            if (reloj != nullptr) { reloj->Stop(); delete reloj; reloj = nullptr; }
        }

    private:
        void Finalizar(bool exito)
        {
            if (terminado) return;
            terminado = true;
            reloj->Stop();
            this->DialogResult = exito ? System::Windows::Forms::DialogResult::OK : System::Windows::Forms::DialogResult::Retry;
            this->Close();
        }

        System::Void Frm_Shown(Object^ sender, EventArgs^ e)
        {
            limiteMemoria = DateTime::Now.AddSeconds(2);
            reloj->Start();
            this->Focus();
        }

        System::Void Reloj_Tick(Object^ sender, EventArgs^ e)
        {
            if (mostrando && DateTime::Now >= limiteMemoria) mostrando = false;
            escena->Invalidate();
        }

        int ObtenerDigito(Keys tecla)
        {
            switch (tecla)
            {
            case Keys::D1: case Keys::NumPad1: return 1;
            case Keys::D2: case Keys::NumPad2: return 2;
            case Keys::D3: case Keys::NumPad3: return 3;
            case Keys::D4: case Keys::NumPad4: return 4;
            case Keys::D5: case Keys::NumPad5: return 5;
            default: return 0;
            }
        }

        System::Void Frm_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (terminado || mostrando) return;
            int digito = ObtenerDigito(e->KeyCode);
            if (digito == 0) return;
            if (digito != entrada + 1) Finalizar(false);
            else
            {
                ++entrada;
                if (entrada >= 5) Finalizar(true);
            }
            e->SuppressKeyPress = true;
            escena->Invalidate();
        }

        System::Void Escena_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            g->SmoothingMode = SmoothingMode::AntiAlias;
            int w = escena->ClientSize.Width;
            g->Clear(Color::FromArgb(22, 22, 35));
            SolidBrush^ blanco = gcnew SolidBrush(Color::FromArgb(243, 240, 229));
            SolidBrush^ tenue = gcnew SolidBrush(Color::FromArgb(160, 164, 181));
            SolidBrush^ dorado = gcnew SolidBrush(Color::FromArgb(214, 174, 101));
            SolidBrush^ tarjeta = gcnew SolidBrush(Color::FromArgb(39, 40, 58));
            Pen^ borde = gcnew Pen(Color::FromArgb(105, 95, 75), 2);
            Drawing::Font^ titulo = gcnew Drawing::Font(L"Georgia", 22, FontStyle::Bold);
            Drawing::Font^ simbolo = gcnew Drawing::Font(L"Georgia", 31, FontStyle::Bold);
            Drawing::Font^ normal = gcnew Drawing::Font(L"Segoe UI", 12, FontStyle::Regular);
            Drawing::Font^ numero = gcnew Drawing::Font(L"Segoe UI", 21, FontStyle::Bold);

            g->DrawString(L"CONCENTRACIÓN", titulo, blanco, 38, 30);
            g->DrawString(mostrando ? L"Observa los símbolos y memoriza su orden." : L"Introduce los números en el mismo orden.", normal, tenue, 42, 78);

            for (int i = 0; i < 5; ++i)
            {
                int x = 65 + i * 137;
                g->FillRectangle(tarjeta, x, 180, 112, 132);
                g->DrawRectangle(borde, x, 180, 112, 132);
                if (mostrando)
                    g->DrawString(simbolos[i], simbolo, dorado, x + 37, 213);
                else
                {
                    String^ contenido = i < entrada ? (i + 1).ToString() : L"?";
                    g->DrawString(contenido, numero, i < entrada ? dorado : blanco, x + 42, 218);
                }
            }

            if (mostrando)
            {
                double ms = Math::Max(0.0, (limiteMemoria - DateTime::Now).TotalMilliseconds);
                float fraccion = static_cast<float>(Math::Min(1.0, ms / 2000.0));
                g->FillRectangle(tarjeta, 42, 367, w - 84, 12);
                g->FillRectangle(dorado, 42, 367, static_cast<int>((w - 84) * fraccion), 12);
                g->DrawString(L"Tienes 2 segundos...", normal, blanco, 42, 397);
            }
            else
            {
                g->DrawString(L"Pulsa 1  →  2  →  3  →  4  →  5", normal, dorado, 42, 375);
                g->DrawString(L"Aciertos: " + entrada.ToString() + L" / 5", normal, blanco, 42, 410);
            }

            delete numero; delete normal; delete simbolo; delete titulo;
            delete borde; delete tarjeta; delete dorado; delete tenue; delete blanco;
        }
    };

    // MINIJUEGO 3
   
    public ref class FrmTemblor : public Form
    {
    private:
        PanelMinijuegoDobleBuffer^ escena;
        Timer^ reloj;
        DateTime limiteRonda;
        DateTime siguientePaso;
        int posicion;
        int direccion;
        int ronda;
        bool terminado;

    public:
        FrmTemblor()
        {
            posicion = 0;
            direccion = 1;
            ronda = 0;
            terminado = false;
            limiteRonda = DateTime::Now.AddSeconds(3);
            siguientePaso = DateTime::Now.AddMilliseconds(140);

            this->Text = L"Controlar el temblor — Crimen y castigo";
            this->ClientSize = Drawing::Size(800, 500);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->KeyPreview = true;
            this->BackColor = Color::FromArgb(29, 21, 24);

            escena = gcnew PanelMinijuegoDobleBuffer();
            escena->Dock = DockStyle::Fill;
            escena->BackColor = this->BackColor;
            escena->Paint += gcnew PaintEventHandler(this, &FrmTemblor::Escena_Paint);
            this->Controls->Add(escena);

            reloj = gcnew Timer();
            reloj->Interval = 20;
            reloj->Tick += gcnew EventHandler(this, &FrmTemblor::Reloj_Tick);
            this->KeyDown += gcnew KeyEventHandler(this, &FrmTemblor::Frm_KeyDown);
            this->Shown += gcnew EventHandler(this, &FrmTemblor::Frm_Shown);
        }

    public:
        ~FrmTemblor()
        {
            if (reloj != nullptr) { reloj->Stop(); delete reloj; reloj = nullptr; }
        }

    private:
        void Finalizar(bool exito)
        {
            if (terminado) return;
            terminado = true;
            reloj->Stop();
            this->DialogResult = exito ? System::Windows::Forms::DialogResult::OK : System::Windows::Forms::DialogResult::Retry;
            this->Close();
        }

        void NuevaRonda()
        {
            posicion = 0;
            direccion = 1;
            limiteRonda = DateTime::Now.AddSeconds(3);
            siguientePaso = DateTime::Now.AddMilliseconds(140);
        }

        System::Void Frm_Shown(Object^ sender, EventArgs^ e)
        {
            NuevaRonda();
            reloj->Start();
            this->Focus();
        }

        System::Void Reloj_Tick(Object^ sender, EventArgs^ e)
        {
            DateTime ahora = DateTime::Now;
            if (ahora >= limiteRonda) { Finalizar(false); return; }
            while (ahora >= siguientePaso)
            {
                posicion += direccion;
                if (posicion >= 18) { posicion = 18; direccion = -1; }
                else if (posicion <= 0) { posicion = 0; direccion = 1; }
                siguientePaso = siguientePaso.AddMilliseconds(140);
            }
            escena->Invalidate();
        }

        System::Void Frm_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (terminado) return;
            if (e->KeyCode == Keys::A) posicion = Math::Max(0, posicion - 1);
            else if (e->KeyCode == Keys::D) posicion = Math::Min(18, posicion + 1);
            else if (e->KeyCode == Keys::Space)
            {
                if (posicion >= 8 && posicion <= 10)
                {
                    ++ronda;
                    if (ronda >= 3) { Finalizar(true); return; }
                    NuevaRonda();
                }
                else { Finalizar(false); return; }
            }
            else return;
            e->SuppressKeyPress = true;
            escena->Invalidate();
        }

        System::Void Escena_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            g->SmoothingMode = SmoothingMode::AntiAlias;
            int w = escena->ClientSize.Width;
            g->Clear(Color::FromArgb(29, 21, 24));
            SolidBrush^ blanco = gcnew SolidBrush(Color::FromArgb(240, 233, 224));
            SolidBrush^ tenue = gcnew SolidBrush(Color::FromArgb(165, 151, 150));
            SolidBrush^ rojo = gcnew SolidBrush(Color::FromArgb(166, 69, 67));
            SolidBrush^ oro = gcnew SolidBrush(Color::FromArgb(224, 174, 99));
            SolidBrush^ fondo = gcnew SolidBrush(Color::FromArgb(48, 37, 40));
            Drawing::Font^ titulo = gcnew Drawing::Font(L"Georgia", 22, FontStyle::Bold);
            Drawing::Font^ normal = gcnew Drawing::Font(L"Segoe UI", 12, FontStyle::Regular);
            Drawing::Font^ grande = gcnew Drawing::Font(L"Georgia", 19, FontStyle::Bold);

            g->DrawString(L"CONTROLA EL TEMBLOR", titulo, blanco, 38, 30);
            g->DrawString(L"Fija el indicador en la zona estable. Repite tres veces.", normal, tenue, 42, 78);
            g->DrawString(L"RONDA " + (ronda + 1).ToString() + L" / 3", grande, oro, 42, 145);

            int inicio = 70;
            int y = 260;
            int pasoX = (w - 140) / 18;
            g->FillRectangle(fondo, 50, 230, w - 100, 76);
            for (int i = 0; i < 19; ++i)
            {
                int x = inicio + i * pasoX;
                SolidBrush^ marca = (i >= 8 && i <= 10) ? gcnew SolidBrush(Color::FromArgb(71, 135, 104)) : gcnew SolidBrush(Color::FromArgb(91, 76, 78));
                g->FillEllipse(marca, x - 8, y - 8, 16, 16);
                delete marca;
            }
            int marcadorX = inicio + posicion * pasoX;
            g->FillEllipse(oro, marcadorX - 13, y - 13, 26, 26);
            g->DrawEllipse(Pens::WhiteSmoke, marcadorX - 15, y - 15, 30, 30);

            double ms = Math::Max(0.0, (limiteRonda - DateTime::Now).TotalMilliseconds);
            float fraccion = static_cast<float>(Math::Min(1.0, ms / 3000.0));
            g->FillRectangle(fondo, 42, 345, w - 84, 13);
            g->FillRectangle(rojo, 42, 345, static_cast<int>((w - 84) * fraccion), 13);
            g->DrawString(L"A: izquierda       D: derecha       ESPACIO: fijar", normal, blanco, 42, 390);
            g->DrawString(L"Zona estable: posiciones 8, 9 y 10", normal, oro, 42, 425);

            delete grande; delete normal; delete titulo;
            delete fondo; delete oro; delete rojo; delete tenue; delete blanco;
        }
    };

} 
