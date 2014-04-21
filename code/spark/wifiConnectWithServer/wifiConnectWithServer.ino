//////////////////////////////
/////// * FIRMWARE * /////////
//////////////////////////////
///created by fito_segrera////
////////April / 2014//////////
//////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//UPLOAD THIS CODE TO THE SPARK CORE: 
//OPTION 1: GO TO https://www.spark.io AND CLICK THE "BUILD" LINK, THIS WILL TAKE YOU
//TO THE ONLINE IDE. CREATE A NEW CODE DOCUMENT AND COPY-PASTE THIS CODE...
//OPTION 2: INSTALL THE SPARK-CLI (TERMINAL COMMANDS TO PROGRAM THE SPARK CORE)
//I RECOMEND THIS SECOND OPTION... TO INSTALL THE CLIENT GO TO: https://github.com/spark/spark-cli
//AND FOLLOW THE INSTRUCTIONS IN THE README FILE.
//////////////////////////////////////////////////////////////////////////////////////////////////
//THIS CODE ONLY SENDS THE MESSAGE ONCE WHEN THE USER DIES... 
//IF YOU WANT TO REUSE THIS SOFTWARE AFTER THE 
//SYSTEM REPORTS THE USER IS DEAD, YOU MUST RESTART THE DEVICE MANUALLY... 
//(RESTART THE SPARK CORE... RESET BUTTON OVER THE BOARD)
//////////////////////////////////////////////////////////////////////////////////////////////////
char resultstr[64];
int pin = 7;
boolean state = false;
int data = 0;

void setup()
{
  pinMode(pin, INPUT);
  Spark.variable("result", &resultstr, STRING);
}

void loop()
{
  data = digitalRead(pin); 
  if(data == 1 && state == false){
    sprintf(resultstr, "\%d", data); 
    delay(1000);
    state = true;
  }else{
    int off = 0;
    sprintf(resultstr, "\%d", off); 
    delay(1000);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

