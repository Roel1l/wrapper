using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace sharpdriver
{
    [StructLayout(LayoutKind.Sequential)]
    public struct MCTLVERSION
    {
        [MarshalAs(UnmanagedType.U4)]
        uint dwType;
        [MarshalAs(UnmanagedType.I4)]
        public int iVerBuilt;
        [MarshalAs(UnmanagedType.I4)]
        public int iVerMajor;
        [MarshalAs(UnmanagedType.I4)]
        public int iVerMinor;
        [MarshalAs(UnmanagedType.I4)]
        public int iVerRelease;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 255)]
        public string szDescription;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 255)]
        public string szComment;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 255)]
        public string szCompanyName;
    }

    class Program
    {
        [DllImport("mctlWrapper.dll")]
        public static extern uint mctlw_GetVersion(ref MCTLVERSION lpMctlVer);

        static void Main(string[] args)
        {
            Console.WriteLine("sizeof(long): " + sizeof(long));
            uint status = 0;
            MCTLVERSION mversion = new MCTLVERSION();
            status = mctlw_GetVersion(ref mversion);
            Console.WriteLine(status);
            Console.WriteLine(mversion.iVerBuilt);
            Console.WriteLine(mversion.iVerMajor);
            Console.WriteLine(mversion.iVerMinor);
            Console.WriteLine(mversion.iVerRelease);
            Console.WriteLine(mversion.szDescription);
            Console.WriteLine(mversion.szComment);
            Console.WriteLine(mversion.szCompanyName);
        }
    }
}
