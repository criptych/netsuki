using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using netsuki;

namespace testsuki
{
   public partial class Form1: Form
   {
      Lua lua = new Lua();

      private class dotnet
      {
         public static void print(string msg)
         {
            Console.WriteLine(msg);
         }
         public static void msgbox(string msg)
         {
            MessageBox.Show(msg, "Message");
         }
         public static bool query(string msg)
         {
            return MessageBox.Show(msg, "Query", MessageBoxButtons.YesNo) == DialogResult.Yes;
         }
         public static string reverse(string text)
         {
            StringBuilder sb = new StringBuilder(text.Length);
            for (int i = 0; i < text.Length; i++)
               sb.Append(text[text.Length - i - 1]);
            return sb.ToString();
         }
      }

      public Form1()
      {
         InitializeComponent();

         lua.RegisterLibrary(typeof(dotnet));
      }

      private void button1_Click(object sender, EventArgs e)
      {
         try
         {
            lua.DoString(textBox1.Text);
         }
         catch (LuaException x)
         {
            MessageBox.Show(x.ToString(), "Lua Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
         }
      }
   }
}
