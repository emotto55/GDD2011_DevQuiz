function myFunction() {
 
  //データ取得
  var response = UrlFetchApp.fetch("http://gdd-2011-quiz-japan.appspot.com/apps_script/data?param=-4693790266312240589");
  //Browser.msgBox(response.getContentText());
  if(response == null) {
    return;
  }
  
  //JSONデータを配列に変換
  var jsondata = eval("("+response.getContentText()+")");
  if(jsondata == null) {
    return;
  }
  
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = SpreadsheetApp.getActiveSheet();
  //Browser.msgBox(sheet.getRange(2, 3).getNumberFormats());
  
  for( var i=0; i<jsondata.length; i++ ) {
  //for( var i=0; i<1; i++ ) {
    //都市名でシート作成し、作成したシートを取得
    ss.insertSheet(jsondata[i].city_name)
    sheet = ss.getSheetByName(jsondata[i].city_name);
    for( var j=0; j<jsondata[i].data.length; j++ ) {
    //for( var j=0; j<1; j++ ) {
      sheet.getRange(j+1, 1).setValue(jsondata[i].data[j].capacity);
      sheet.getRange(j+1, 2).setValue(jsondata[i].data[j].usage);
      //C列には計算式を記載
      sheet.getRange(j+1, 3).setValue("=" + sheet.getRange(j+1, 2).getValue() + "/" + sheet.getRange(j+1, 1).getValue());
      //sheet.getRange(j+1, 3).setNumberFormat("0.00%");
    }
    //サンプルを見ると、データは数値だったり式であったりしたが、
    //表示形式は"0.00%"に統一されているようなのでここで設定
    sheet.getRange("C1:C"+j).setNumberFormat("0.00%");
  }
}
