Process printProcess = new Process();
 printProcess.StartInfo = printProcessInfo;
 printProcess.Start();
 printProcess.WaitForInputIdle();
 Thread.Sleep(3000);
 if (false == printProcess.CloseMainWindow())
 {
 printProcess.Kill();
 }
ReportDocument rpt = new ReportDocument();
rpt.Load(@"C:\CrystalReport1.rpt");
rpt.SetDataSource(datatablesource);
ExportOptions rptExportOption;
DiskFileDestinationOptions rptFileDestOption = new DiskFileDestinationOptions();
PdfRtfWordFormatOptions rptFormatOption = new PdfRtfWordFormatOptions();
string reportFileName = @"C:\Kimlik.pdf";
rptFileDestOption.DiskFileName = reportFileName;
rptExportOption = rpt.ExportOptions;
{
 rptExportOption.ExportDestinationType = ExportDestinationType.DiskFile;
 rptExportOption.ExportFormatType = ExportFormatType.PortableDocFormat;
 rptExportOption.ExportDestinationOptions = rptFileDestOption;
 rptExportOption.ExportFormatOptions = rptFormatOption;
}
 rpt.Export();
