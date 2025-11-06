using System;
using System.IO;
using System.Windows;
using System.Runtime.InteropServices;

namespace NotesAppUI
{
    public partial class MainWindow : Window
    {
        [DllImport("TranslatorCore.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TranslateText([MarshalAs(UnmanagedType.LPStr)] string text, [MarshalAs(UnmanagedType.LPStr)] string targetLang);

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            string file = "notes.txt";
            File.AppendAllText(file, $"[{TitleBox.Text}]\n{NoteBox.Text}\n\n");
            MessageBox.Show("メモを保存しました！");
        }

        private void Translate_Click(object sender, RoutedEventArgs e)
        {
            string input = NoteBox.Text;
            IntPtr resultPtr = TranslateText(input, "ja");
            string translated = Marshal.PtrToStringAnsi(resultPtr);
            NoteBox.Text = translated;
        }
    }
}
