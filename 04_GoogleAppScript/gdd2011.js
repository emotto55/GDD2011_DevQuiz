function myFunction() {
 
  //�f�[�^�擾
  var response = UrlFetchApp.fetch("http://gdd-2011-quiz-japan.appspot.com/apps_script/data?param=-4693790266312240589");
  //Browser.msgBox(response.getContentText());
  if(response == null) {
    return;
  }
  
  //JSON�f�[�^��z��ɕϊ�
  var jsondata = eval("("+response.getContentText()+")");
  if(jsondata == null) {
    return;
  }
  
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = SpreadsheetApp.getActiveSheet();
  //Browser.msgBox(sheet.getRange(2, 3).getNumberFormats());
  
  for( var i=0; i<jsondata.length; i++ ) {
  //for( var i=0; i<1; i++ ) {
    //�s�s���ŃV�[�g�쐬���A�쐬�����V�[�g���擾
    ss.insertSheet(jsondata[i].city_name)
    sheet = ss.getSheetByName(jsondata[i].city_name);
    for( var j=0; j<jsondata[i].data.length; j++ ) {
    //for( var j=0; j<1; j++ ) {
      sheet.getRange(j+1, 1).setValue(jsondata[i].data[j].capacity);
      sheet.getRange(j+1, 2).setValue(jsondata[i].data[j].usage);
      //C��ɂ͌v�Z�����L��
      sheet.getRange(j+1, 3).setValue("=" + sheet.getRange(j+1, 2).getValue() + "/" + sheet.getRange(j+1, 1).getValue());
      //sheet.getRange(j+1, 3).setNumberFormat("0.00%");
    }
    //�T���v��������ƁA�f�[�^�͐��l�������莮�ł������肵�����A
    //�\���`����"0.00%"�ɓ��ꂳ��Ă���悤�Ȃ̂ł����Őݒ�
    sheet.getRange("C1:C"+j).setNumberFormat("0.00%");
  }
}
