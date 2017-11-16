using System;

using System.Runtime.InteropServices;

namespace MotionControl
{
   class DLLT
   {
      [DllImport("user32.dll")]
      public static extern IntPtr MessageBox(int hWnd, String text,
                                         String caption, uint type);
   }
   class MCTL
   {
      [DllImport("C:\\CNCWorkbench\\control\\can\\canapi.dll")]
      public static extern uint mctl_Initialize(string cfile);
      [DllImport("C:\\CNCWorkbench\\control\\can\\canapi.dll")]
      public static extern uint mctl_Exit();
   }

   class AXCTL
   {
       [DllImport("C:\\CNCWorkbench\\control\\can\\axctl.dll")]
      public static extern uint axctl_Initialize(string cfile);
       [DllImport("C:\\CNCWorkbench\\control\\can\\axctl.dll")]
      public static extern uint axctl_Reset(uint hAxis);
       [DllImport("C:\\CNCWorkbench\\control\\can\\axctl.dll")]
      public static extern uint axctl_Reference(uint hAxis);
       [DllImport("C:\\CNCWorkbench\\control\\can\\axctl.dll")]
      public static extern uint axctl_MoveAbs(uint hAxis, int ipos);
       [DllImport("C:\\CNCWorkbench\\control\\can\\axctl.dll")]
      public static extern uint axctl_Exit();

   }
}

