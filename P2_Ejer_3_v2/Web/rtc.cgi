t <html><head><title>RTC Control</title></head>
i pg_header.inc
t <h2 align=center><br>Modulo de Control del RTC</h2>
t <p><font size="2">Esta página muestra el valor del tiempo y la fecha del <b>Modulo RTC</b>.
#t  Simply enter the text which you want to display and click <b>Send</b>.<br><br>
#t  This Form uses a <b>POST</b> method to send data to a Web server.</font></p>
t <form action=rtc.cgi method=post name=cgi>
t <input type=hidden value="rtc" name=pg>
t <table border=0 width=99%><font size="3">
t <tr bgcolor=#aaccff>
t  <th width=40%>Item</th>
t  <th width=60%>Setting</th></tr>
# Here begin data setting which is formatted in HTTP_CGI.C module
t <tr><td><img src=pabb.gif>Tiempo</td>
c f 1 <td><<div id="ID" class="clock" onload="showTime()"></div>></td></tr>
t <tr><td><img src=pabb.gif>Fecha</TD>
c f 2 <td><input type=text name=lcd2 size=20 maxlength=20 value="%s"></td></tr>
t </font></table>
# Here begin button definitions
#t <p align=center>
#t <input type=submit name=set value="Send" id="sbm">
#t <input type=reset value="Undo">
#t </p></form>
i pg_footer.inc
. End of script must be closed with period.
