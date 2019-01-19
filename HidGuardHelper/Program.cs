using System.Diagnostics;
using System.Threading;
using UtilLibrary;

namespace HidGuardHelper
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Process.GetCurrentProcess().PriorityClass =
                    ProcessPriorityClass.Idle;
            }
            catch { } // Ignore problems raising the priority.

            bool foundId = false;
            int processId = 0;
            if (args.Length == 1)
            {
                foundId = int.TryParse(args[0], out processId);
            }
            
            if (foundId)
            {
                string[] wlEntries = Class1.HidGuardWhitelist();
                foreach (string entry in wlEntries)
                {
                    Class1.DeleteSubKey(entry);
                }

                ProcessWatch watcher = null;
                Thread temp = new Thread(() =>
                {
                    watcher = new ProcessWatch(processId);
                    if (watcher.ProcessExists)
                    {
                        Class1.CreateSubKey(@"SYSTEM\CurrentControlSet\Services\HidGuardian\Parameters\Whitelist\");
                        Class1.CreateSubKey(@"SYSTEM\CurrentControlSet\Services\HidGuardian\Parameters\Whitelist\"
+ processId, Class1.REGISTRY_OPTION_VOLATILE);
                    }
                });
                temp.Priority = ThreadPriority.Lowest;
                temp.Start();
                temp.Join();
                
                if (watcher.ProcessExists)
                    watcher.lostProcess.WaitOne();

                Class1.DeleteSubKey(@"SYSTEM\CurrentControlSet\Services\HidGuardian\Parameters\Whitelist\"
+ processId);
            }
        }
    }
}
