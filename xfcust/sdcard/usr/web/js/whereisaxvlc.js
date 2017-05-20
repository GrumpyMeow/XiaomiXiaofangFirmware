AxvlcProtocal = 'ftp://';
AxvlcUser = 'inftp_sa3';
AxvlcPasswd = 'sa3';
AxvlcAddress = 'inftp.sonix.com.tw';
AxvlcPath = '/';
ObjectBegin = '<object codebase="';
AxvlcURL = AxvlcProtocal + AxvlcUser +':' + AxvlcPasswd + '@' + AxvlcAddress + AxvlcPath;
AxvlcCab = 'axvlc.cab#version=2,0,2,0" classid="clsid:9BE31822-FDAD-461B-AD51-BE1D1C159921" id="mymovie"';
WidthHeight = ' width="640" height="480" ';
CloseAngle = '>';
EmbedBegin = '<EMBED pluginspage="' + AxvlcURL + 'axvlc.cab"' +' type="application/x-vlc-plugin" version="VideoLAN.VLCPlugin.2" '
EmbedEnd = ' toolbar="false" id="mymovie"></EMBED>'
ObjectEnd = '</object>';
AxvlcObject = ObjectBegin + AxvlcURL + AxvlcCab + WidthHeight +CloseAngle + EmbedBegin + WidthHeight + EmbedEnd +ObjectEnd;
