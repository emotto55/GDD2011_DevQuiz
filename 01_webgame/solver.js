
//全てのカードの背景色取得
var elements = document.getElementsByClassName("card"); 
if (elements == null) {
  alert('Card element is not found. Check element id.');
} else {
  var res;
  var element;
  
  //クリックイベント作成
  var myevent = document.createEvent('MouseEvents');
  myevent.initEvent('click', false, true);
  
  var cardlist = [];
  //各Cardの背景色取得
  for( var j=0; j<elements.length; j++ ) {
    //res += elements.item(j).nodeName + "：" + elements.item(j).className + "：" + elements.item(j).id + "\n";
    element = elements.item(j);
    element.dispatchEvent(myevent);
    var cardinfo = {};
    cardinfo["color"] = element.style.backgroundColor;
    cardinfo["opened"] = false;
    cardlist[j] = cardinfo;  
  }
  //Open済かどうかチェック
  for( var j=0; j<elements.length; j++ ) {
    element = elements.item(j);
    var style = element.style.backgroundColor;
    if(style == cardlist[j]["color"]) {
      cardlist[j]["opened"] = true;
    }
  }
  
  //色が同じCardを開けていく
  for( var j=0; j<elements.length; j++ ) {
    if(cardlist[j]["opened"] == false) {
      var temp = cardlist[j]["color"];
      for( var k=j; k<elements.length; k++ ) {
        if(cardlist[k]["color"] == temp) {
          elements.item(j).dispatchEvent(myevent);
          elements.item(k).dispatchEvent(myevent);
          cardlist[j]["opened"] = true;
          cardlist[k]["opened"] = true;
        }
      }
    } 
  }
  
}

