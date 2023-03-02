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
t  <th width=40%>Variable</th>
t  <th width=60%>Valores</th></tr>
# Here begin data setting which is formatted in HTTP_CGI.C module
t <tr><td><img src=pabb.gif>Tiempo</td>
t <td align="center"><input type="text" readonly style="background-color: transparent; border: 0px"
c f 1 size="10" id="rtc_time_value" value="%s"></td></tr>
t <tr><td><img src=pabb.gif>Fecha</TD>
t <td align="center"><input type="text" readonly style="background-color: transparent; border: 0px"
c f 2 size="10" id="rtc_date_value" value="%s"></td></tr>
t </font></table>
# Here begin button definitions
#t <p align=center>
#t <input type=submit name=set value="Send" id="sbm">
#t <input type=reset value="Undo">
#t </p></form>
i pg_footer.inc
. End of script must be closed with period.
