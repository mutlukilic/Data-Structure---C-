Process printProcess = new Process();
 printProcess.StartInfo = printProcessInfo;
 printProcess.Start();
 printProcess.WaitForInputIdle();
 Thread.Sleep(3000);
 if (false == printProcess.CloseMainWindow())
 {
 printProcess.Kill();
 }
