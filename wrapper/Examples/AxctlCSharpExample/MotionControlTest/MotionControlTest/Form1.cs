using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MotionControl;

namespace MotionControlTest
{
   public partial class Form1 : Form
   {
      public Form1()
      {
         InitializeComponent();
      }

      private void button1_Click(object sender, EventArgs e)
      {
         uint uiResult = 0;
         string strTest;
//         uiResult = MCTL.mctl_Initialize("C:\\CNCWorkbench\\control\\can\\testaxctlserial.ini");
//         uiResult = 0;
//          if ((0xC000FFFF & uiResult) == 0)
//         {
             // mctl_Initialize erfolgreich
             uiResult = AXCTL.axctl_Initialize("C:\\CNCWorkbench\\control\\can\\testaxctlserial.ini");
             if ((uiResult & 0xC000FFFF) == 0)
             {
                 // axctl_Initialize erfolgreich
                 // Reset der ersten Achse
                 uiResult = AXCTL.axctl_Reset(1);
                 if ((uiResult & 0xC000FFFF) == 0)
                 {
                     uiResult = AXCTL.axctl_Reference(1);
                     if ((uiResult & 0xC000FFFF) == 0)
                     {
                         strTest = string.Format("{0:X}", uiResult);
                         uiResult = AXCTL.axctl_MoveAbs(1, 10000);
                         if ((uiResult & 0xC000FFFF) == 0)
                         {
                             DLLT.MessageBox(0, "Warten Sie bis Bewegung zu Ende, dann MessageBox schliessen", "Ende", 0);
                             uiResult = AXCTL.axctl_Exit();
                             uiResult = MCTL.mctl_Exit();
                         }
                         else
                         {
                             strTest = string.Format("{0:X}", uiResult);
                             DLLT.MessageBox(0, strTest, "Fehler bei axctl_MoveAbs", 0);
                         }
                     }
                     else
                     {
                         strTest = string.Format("{0:X}", uiResult);
                         DLLT.MessageBox(0, strTest, "Fehler bei axctl_Reference", 0);
                     }
                 }
                 else
                 {
                     strTest = string.Format("{0:X}", uiResult);
                     DLLT.MessageBox(0, strTest, "Fehler bei axctl_Reset", 0);
                 }
             }
             else
             {
                 strTest = string.Format("{0:X}", uiResult);
                 DLLT.MessageBox(0, strTest, "Fehler bei axctl_Initialize", 0);
             }
//         }
//         else
//         {
//             strTest = string.Format("{0:X}", uiResult);
//             DLLT.MessageBox(0, strTest, "Fehler bei mctl_Initialize", 0);
//         }
      }
   }
}
