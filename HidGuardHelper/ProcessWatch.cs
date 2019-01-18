using System.Diagnostics;
using System.Threading;

namespace HidGuardHelper
{
    class ProcessWatch
    {
        private Timer processChecker;
        //private Timer _processChecker;
        private int processId;
        private bool processExists;
        public bool ProcessExists => processExists;
        public readonly ManualResetEvent lostProcess = new ManualResetEvent(false);

        public ProcessWatch(int processId)
        {
            this.processId = processId;
            try
            {
                Process.GetProcessById(processId);
                processExists = true;
            }
            catch { processExists = false; }
            
            if (processExists)
            {
                processChecker = new Timer(ProcessCheckElapsed,
                    null, 1000, 1000);
                /*_processChecker = new Timer(1000);
                _processChecker.AutoReset = false;
                _processChecker.Elapsed += ProcessCheckElapsed;
                _processChecker.Start();
                */
            }
        }

        private void ProcessCheckElapsed(object state)
        //private void ProcessCheckElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            //_processChecker.Stop();

            try
            {
                Process.GetProcessById(processId);
            }
            catch { processExists = false; }

            //if (processExists)
            //{
            //_processChecker.Start();
            //}
            //else
            if (!processExists)
            {
                processChecker.Dispose();
                lostProcess.Set();
            }
        }
    }
}
