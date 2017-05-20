function list(){
    var i;
    var type = document.getElementById("type").value;
    for (i = 10; i < 52; i++) {
		$("#"+i).addClass("hidden");
        //document.getElementById(i).style.display = "none";
    }
    if (type == "wep") {
    
        for (var n = 10; n < 14; n++) {
            //var t = document.getElementById(n);
            //t.style.display = "";
			$("#"+n).removeClass("hidden");			
        }
        
        if (document.getElementById("key64").checked) {
            if (document.getElementById("keytype1").checked) {
                for (var n = 14; n < 18; n++) {
                    //document.getElementById(n).style.display = "";
					$("#"+n).removeClass("hidden");
                }
            }
            else 
                if (document.getElementById("keytype2").checked) {
                    for (var n = 18; n < 26; n++) {
                        //document.getElementById(n).style.display = "";
						$("#"+n).removeClass("hidden");
                    }
                }
                else {
                    for (var n = 26; n < 31; n++) {
                        //document.getElementById(n).style.display = "";
						$("#"+n).removeClass("hidden");
                    }
                }
        }
        else {
            if (document.getElementById("keytype1").checked) {
                for (var n = 31; n < 35; n++) {
                    //document.getElementById(n).style.display = "";
					$("#"+n).removeClass("hidden");
                }
            }
            else 
                if (document.getElementById("keytype2").checked) {
                    for (var n = 35; n < 43; n++) {
                        //document.getElementById(n).style.display = "";
						$("#"+n).removeClass("hidden");
                    }
                }
                else {
                    //document.getElementById("26").style.display = "";
					$("#26").removeClass("hidden");
                    for (var n = 43; n < 47; n++) {
                        //document.getElementById(n).style.display = "";
						$("#"+n).removeClass("hidden");
                    }
                }
        }
    }
    else 
        if (type == "wpa") {
            for (var n = 47; n < 52; n++) {
                //document.getElementById(n).style.display = "";
				$("#"+n).removeClass("hidden");
            }
            if (document.getElementById("mode1").checked) {
                //document.getElementById('51').style.display = 'none';
                //document.getElementById('50').style.display = '';
				$("#51").addClass("hidden");
				$("#50").removeClass("hidden");
            }
            else {
                //document.getElementById('50').style.display = 'none';
                //document.getElementById('51').style.display = '';
				$("#50").addClass("hidden");
				$("#51").removeClass("hidden");				
            }
        }
}

function start_time(){
    setTimeout("window.location.href='/cgi-bin/wireless.cgi?op=wireless&action=error'", 90000);
}

function convertAsciiToHex(string){
    var decCharCode = ""
    var hexChars = "0123456789ABCDEF"
    var hexString = ""
    for (i = 0; i < string.length; i++) {
        decCharCode = string.charCodeAt([i])
        var h2 = decCharCode % 16
        var h1 = (decCharCode - h2) / 16
        hexString += hexChars.charAt(h1)
        hexString += hexChars.charAt(h2)
    }
    return hexString
}

function change_fun(form, to){
    var f = form;
    var t = document.getElementById(to);
    t.value = convertAsciiToHex(f.value);
}

var debug_on = false;
/* var debug_on = true;*/

var low_16_bits = 0xFFFF;

var t = new Array(65);

t[1] = -680876936
t[2] = -389564586
t[3] = 606105819
t[4] = -1044525330
t[5] = -176418897
t[6] = 1200080426
t[7] = -1473231341
t[8] = -45705983
t[9] = 1770035416
t[10] = -1958414417
t[11] = -42063
t[12] = -1990404162
t[13] = 1804603682
t[14] = -40341101
t[15] = -1502002290
t[16] = 1236535329
t[17] = -165796510
t[18] = -1069501632
t[19] = 643717713
t[20] = -373897302
t[21] = -701558691
t[22] = 38016083
t[23] = -660478335
t[24] = -405537848
t[25] = 568446438
t[26] = -1019803690
t[27] = -187363961
t[28] = 1163531501
t[29] = -1444681467
t[30] = -51403784
t[31] = 1735328473
t[32] = -1926607734
t[33] = -378558
t[34] = -2022574463
t[35] = 1839030562
t[36] = -35309556
t[37] = -1530992060
t[38] = 1272893353
t[39] = -155497632
t[40] = -1094730640
t[41] = 681279174
t[42] = -358537222
t[43] = -722521979
t[44] = 76029189
t[45] = -640364487
t[46] = -421815835
t[47] = 530742520
t[48] = -995338651
t[49] = -198630844
t[50] = 1126891415
t[51] = -1416354905
t[52] = -57434055
t[53] = 1700485571
t[54] = -1894986606
t[55] = -1051523
t[56] = -2054922799
t[57] = 1873313359
t[58] = -30611744
t[59] = -1560198380
t[60] = 1309151649
t[61] = -145523070
t[62] = -1120210379
t[63] = 718787259
t[64] = -343485551

function T(x){
    return t[x];
}


/* The different function found in MD5*/

function F(X, Y, Z){
    var A = ((X & Y));
    var B = ((((~ X)) & Z));
    return ((A | B))
}

function G(X, Y, Z){
    var A = ((X & Z));
    var B = ((((~ Z)) & Y));
    return ((A | B))
}

function H(X, Y, Z){
    var A = ((X ^ Y));
    return ((A ^ Z))
}

function I(X, Y, Z){
    var B = (X | ((~ Z)));
    return ((Y ^ B));
}


function rotate(x, y){
    return (x << y) | (x >>> (32 - y));
    
}


function shift_left(x, y){
    return (x << y);
}

function shift_right(x, y){
    return (x >> y);
}

function add_(x, y){
    var l = (x & low_16_bits) + (y & low_16_bits);
    var h = (x >> 16) + (y >> 16) + (l >> 16);
    var result = (((h << 16)) | (l & low_16_bits));
    
    return result;
}



function func_abcdksi(a, b, s, Xk, Ti, Z){
    var A = add_(add_(add_(a, Z), Xk), Ti);
    var B = rotate(A, s);
    
    return add_(b, B);
    
}

function FF(a, b, c, d, s, Xk, Ti){

    return func_abcdksi(a, b, s, Xk, Ti, F(b, c, d));
    
}

function GG(a, b, c, d, s, Xk, Ti){
    return func_abcdksi(a, b, s, Xk, Ti, G(b, c, d));
}

function HH(a, b, c, d, s, Xk, Ti){
    return func_abcdksi(a, b, s, Xk, Ti, H(b, c, d))
}

function II(a, b, c, d, s, Xk, Ti){
    return func_abcdksi(a, b, s, Xk, Ti, I(b, c, d));
}

function md5_main(X, length){

    var A = 1732584193;
    var B = -271733879;
    var C = -1732584194;
    var D = 271733878;
    
    if (debug_on) {
        document.writeln("<br>");
        document.writeln("length = " + X.length + 1);
        document.writeln("<br>");
    }
    
    for (var i = 0; i < X.length; i += 16) {
        var AA = A;
        var BB = B;
        var CC = C;
        var DD = D;
        
        /* Round 1 - Function F */
        A = FF(A, B, C, D, 7, X[i + 0], T(1));
        D = FF(D, A, B, C, 12, X[i + 1], T(2));
        C = FF(C, D, A, B, 17, X[i + 2], T(3));
        B = FF(B, C, D, A, 22, X[i + 3], T(4));
        
        A = FF(A, B, C, D, 7, X[i + 4], T(5));
        D = FF(D, A, B, C, 12, X[i + 5], T(6));
        C = FF(C, D, A, B, 17, X[i + 6], T(7));
        B = FF(B, C, D, A, 22, X[i + 7], T(8));
        
        A = FF(A, B, C, D, 7, X[i + 8], T(9));
        D = FF(D, A, B, C, 12, X[i + 9], T(10));
        C = FF(C, D, A, B, 17, X[i + 10], T(11));
        B = FF(B, C, D, A, 22, X[i + 11], T(12));
        
        A = FF(A, B, C, D, 7, X[i + 12], T(13));
        D = FF(D, A, B, C, 12, X[i + 13], T(14));
        C = FF(C, D, A, B, 17, X[i + 14], T(15));
        B = FF(B, C, D, A, 22, X[i + 15], T(16));
        
        /* Round 2 - Function G */
        A = GG(A, B, C, D, 5, X[i + 1], T(17));
        D = GG(D, A, B, C, 9, X[i + 6], T(18));
        C = GG(C, D, A, B, 14, X[i + 11], T(19));
        B = GG(B, C, D, A, 20, X[i + 0], T(20));
        
        A = GG(A, B, C, D, 5, X[i + 5], T(21));
        D = GG(D, A, B, C, 9, X[i + 10], T(22));
        C = GG(C, D, A, B, 14, X[i + 15], T(23));
        B = GG(B, C, D, A, 20, X[i + 4], T(24));
        
        A = GG(A, B, C, D, 5, X[i + 9], T(25));
        D = GG(D, A, B, C, 9, X[i + 14], T(26));
        C = GG(C, D, A, B, 14, X[i + 3], T(27));
        B = GG(B, C, D, A, 20, X[i + 8], T(28));
        
        A = GG(A, B, C, D, 5, X[i + 13], T(29));
        D = GG(D, A, B, C, 9, X[i + 2], T(30));
        C = GG(C, D, A, B, 14, X[i + 7], T(31));
        B = GG(B, C, D, A, 20, X[i + 12], T(32));
        
        /* Round 3 - Function H */
        A = HH(A, B, C, D, 4, X[i + 5], T(33));
        D = HH(D, A, B, C, 11, X[i + 8], T(34));
        C = HH(C, D, A, B, 16, X[i + 11], T(35));
        B = HH(B, C, D, A, 23, X[i + 14], T(36));
        
        A = HH(A, B, C, D, 4, X[i + 1], T(37));
        D = HH(D, A, B, C, 11, X[i + 4], T(38));
        C = HH(C, D, A, B, 16, X[i + 7], T(39));
        B = HH(B, C, D, A, 23, X[i + 10], T(40));
        
        A = HH(A, B, C, D, 4, X[i + 13], T(41));
        D = HH(D, A, B, C, 11, X[i + 0], T(42));
        C = HH(C, D, A, B, 16, X[i + 3], T(43));
        B = HH(B, C, D, A, 23, X[i + 6], T(44));
        
        A = HH(A, B, C, D, 4, X[i + 9], T(45));
        D = HH(D, A, B, C, 11, X[i + 12], T(46));
        C = HH(C, D, A, B, 16, X[i + 15], T(47));
        B = HH(B, C, D, A, 23, X[i + 2], T(48));
        
        /* Round 4 - Function I */
        A = II(A, B, C, D, 6, X[i + 0], T(49));
        D = II(D, A, B, C, 10, X[i + 7], T(50));
        C = II(C, D, A, B, 15, X[i + 14], T(51));
        B = II(B, C, D, A, 21, X[i + 5], T(52));
        
        A = II(A, B, C, D, 6, X[i + 12], T(53));
        D = II(D, A, B, C, 10, X[i + 3], T(54));
        C = II(C, D, A, B, 15, X[i + 10], T(55));
        B = II(B, C, D, A, 21, X[i + 1], T(56));
        
        A = II(A, B, C, D, 6, X[i + 8], T(57));
        D = II(D, A, B, C, 10, X[i + 15], T(58));
        C = II(C, D, A, B, 15, X[i + 6], T(59));
        B = II(B, C, D, A, 21, X[i + 13], T(60));
        
        A = II(A, B, C, D, 6, X[i + 4], T(61));
        D = II(D, A, B, C, 10, X[i + 11], T(62));
        C = II(C, D, A, B, 15, X[i + 2], T(63));
        B = II(B, C, D, A, 21, X[i + 9], T(64));
        
        A = add_(A, AA);
        B = add_(B, BB);
        C = add_(C, CC);
        D = add_(D, DD);
        
        /*    document.writeln(array_to_hex(new Array(A,B,C,D)));*/
    
    
    }
    
    return Array(A, B, C, D);
}

/* Returns a padded array representation of the string x. */

function text_to_padded_array(x){

    var a = Array();
    var k = x.length;
    
    for (var i = 0; i < x.length; i++) {
        a[shift_right(i, 2)] |= shift_left((x.charCodeAt(i) & 0xFF), ((i % 4) * 8));
    }
    
    /* PAD */
    a[shift_right(k, 2)] |= shift_left(0x80, ((k % 4) * 8));
    
    var a_size = shift_right(k, 2) + 2;
    var length_pos = a_size - (a_size % 16) + 14;
    a[length_pos] = k * 8;
    
    if (debug_on) {
        document.writeln("<br>");
        document.writeln(array_to_hex(a));
        document.writeln("<br>length_pos = " + length_pos);
        document.writeln("<br>a_size = " + a_size);
    }
    
    return a;
}

/* Take a array of 32 bit numbers and convert it to a hex string*/
function array_to_hex(x){
    var hexstring = "0123456789ABCDEF";
    /*  var hexstring = "0123456789abcdef"; */
    var output_string = "";
    
    for (var i = 0; i < x.length * 4; i++) {
        var tmp_i = shift_right(i, 2);
        
        output_string += hexstring.charAt((shift_right(x[tmp_i], ((i % 4) * 8 + 4))) & 0xF) +
        hexstring.charAt(shift_right(x[tmp_i], ((i % 4) * 8)) & 0xF);
    }
    return output_string;
}


/* Calculates a MD5 Message-Digest of the string x and returns it as a 
 * hexadecimal string.
 */
function hex_md5(x){
    if (debug_on) {
        document.writeln("<hr>");
        document.writeln("<br>Indata: '" + x + "'<br>");
    }
    
    return array_to_hex(md5_main(text_to_padded_array(x), x.length));
}


function md5_test_func(x, y){
    document.write("<br>String: " + x);
    if (hex_md5(x).toLowerCase() == y.toLowerCase()) {
        document.write(" (OK!)");
    }
    else {
        document.write(" (FAILED!)");
        document.write("<br>X=" + x);
        document.write("<br>Y=" + y);
        document.write("<br>MD5(x)=" + hex_md5(x));
        document.write("<br>x.length=" + x.length);
        
    }
}

/* These strings are taken from RFC 1321 */

function md5_test(){
    var a = "";
    var a1 = "D41D8CD98F00B204E9800998ECF8427E";
    var b = "a";
    var b1 = "0CC175B9C0F1B6A831C399E269772661";
    var c = "abc";
    var c1 = "900150983CD24FB0D6963F7D28E17F72";
    var d = "message digest";
    d1 = "F96B697D7CB7938D525A2F31AAF161D0";
    var e = "abcdefghijklmnopqrstuvwxyz";
    var e1 = "C3FCD3D76192E4007DFB496CCA67E13B";
    var f = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    var f1 = "D174AB98D277D9F5A5611C2C9F419D9F";
    
    var g = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    var g1 = "57EDF4A22BE3C955AC49DA2E2107B67A";
    
    md5_test_func(a, a1);
    md5_test_func(b, b1);
    md5_test_func(c, c1);
    md5_test_func(d, d1);
    md5_test_func(e, e1);
    md5_test_func(f, f1);
    md5_test_func(g, g1);
    
}



function setHex64FromPhrase(){
    var form = document.getElementById("form1")
    
    var aSeed = 0
    var i, ix
    var aKeys = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    var passphrase = form.Key_WEP_Passphrase64.value
    if (form.Key_WEP_Passphrase128.value != passphrase) {
        form.Key_WEP_Passphrase128.value = passphrase
        setHex128FromPhrase()
    }
    var hexChars = "0123456789ABCDEF"
    var hexString = ""
    var decCharCode
    for (i = 0; i < passphrase.length; i++) {
        var aShift = i & 0x3;
        aSeed = aSeed ^ (passphrase.charCodeAt(i) << (aShift * 8));
    }
    /* Generate keys from seed */
    for (i = 0; i < 20; i++) {
        aSeed = (aSeed * 0x343fd) & 0xFFFFFFFF;
        aSeed = (aSeed + 0x269ec3) & 0xFFFFFFFF;
        aKeys[i] = ((aSeed >> 16) & 0xFF);
    }
    hexString = "";
    for (i = 0; i < 5; i++) {
        decCharCode = aKeys[i]
        var h2 = decCharCode % 16
        var h1 = (decCharCode - h2) / 16
        hexString += hexChars.charAt(h1)
        hexString += hexChars.charAt(h2)
    }
    form.Key1_Gen64p.value = hexString
    hexString = "";
    for (i = 5; i < 10; i++) {
        decCharCode = aKeys[i]
        var h2 = decCharCode % 16
        var h1 = (decCharCode - h2) / 16
        hexString += hexChars.charAt(h1)
        hexString += hexChars.charAt(h2)
    }
    form.Key2_Gen64p.value = hexString
    hexString = "";
    for (i = 10; i < 15; i++) {
        decCharCode = aKeys[i]
        var h2 = decCharCode % 16
        var h1 = (decCharCode - h2) / 16
        hexString += hexChars.charAt(h1)
        hexString += hexChars.charAt(h2)
    }
    form.Key3_Gen64p.value = hexString
    hexString = "";
    for (i = 15; i < 20; i++) {
        decCharCode = aKeys[i]
        var h2 = decCharCode % 16
        var h1 = (decCharCode - h2) / 16
        hexString += hexChars.charAt(h1)
        hexString += hexChars.charAt(h2)
    }
    form.Key4_Gen64p.value = hexString
}

function setHex128FromPhrase(){
    var form = document.getElementById("form1")
    
    var passphrase = form.Key_WEP_Passphrase128.value
    if (form.Key_WEP_Passphrase64.value != passphrase) {
        form.Key_WEP_Passphrase64.value = passphrase
        setHex64FromPhrase();
    }
    var rawstring = passphrase;
    if (passphrase.length == 0) {
        return;
    }
    while (rawstring.length < 64) {
        rawstring = rawstring + passphrase;
    }
    rawstring = rawstring.substr(0, 64);
    var hexstring = hex_md5(rawstring);
    hexstring = hexstring.substr(0, 26);
    form.Key1_Gen128p.value = hexstring
    form.Key2_Gen128p.value = hexstring
    form.Key3_Gen128p.value = hexstring
    form.Key4_Gen128p.value = hexstring
}

function getEBid(str){
    return document.getElementById(str);
}

function err_length(){
    alert(WL_3key_length_err);
    return false;
}

function setHex(str){
    var i = 0;
    var mode = "0123456789ABCDEF";
    var ret = -1;
    str = str.toUpperCase();
    for (i = 0; i < str.length; i++) {
        ret = mode.indexOf(str.charAt(i));
        if (ret == -1) {
            alert(WL_3key_hex_err);
            return false;
        }
    }
    return true;
}

function last_check(){
    var type = getEBid("type");
    var target;
    if (type.value == "no") {
        return true;
    }
    else 
        if (type.value == "wpa") {
            var wpa_type = getEBid("mode1");
            if (wpa_type.checked == true) {
                target = getEBid("64Key");
                if (target.value.length != 64) {
                    return err_length();
                }
                else {
                    return setHex(target.value);
                }
            }
            else {
                target = getEBid("Passphrase");
                if (target.value.length < 8) {
                    return err_length();
                }
                else {
                    return true;
                }
            }
        }
        else 
            if (type.value == "wep") {
                var keylength64 = getEBid("key64");
                var keylength128 = getEBid("key128");
                var keytypeManual = getEBid("keytype1");
                var keytypeAscii = getEBid("keytype2");
                if (keylength64.checked == true) {
                    if (keytypeManual.checked == true) {
                        var mark1 = getEBid("64_m_key1");
                        var mark2 = getEBid("64_m_key2");
                        var mark3 = getEBid("64_m_key3");
                        var mark4 = getEBid("64_m_key4");
                        if (mark1.checked) {
                            target = getEBid("64_m_keytext1");
                        }
                        else 
                            if (mark2.checked) {
                                target = getEBid("64_m_keytext2");
                            }
                            else 
                                if (mark3.checked) {
                                    target = getEBid("64_m_keytext3");
                                }
                                else 
                                    if (mark4.checked) {
                                        target = getEBid("64_m_keytext4");
                                    }
                        if (setHex(target.value) == false) {
                            return false;
                        }
                        if (target.value.length != 10) {
                            return err_length();
                        }
                        else {
                            return setHex(target.value);
                        }
                    }
                    else 
                        if (keytypeAscii.checked == true) {
                            var mark1 = getEBid("64_a_key1");
                            var mark2 = getEBid("64_a_key2");
                            var mark3 = getEBid("64_a_key3");
                            var mark4 = getEBid("64_a_key4");
                            if (mark1.checked) {
                                target = getEBid("64_A_keytext1");
                            }
                            else 
                                if (mark2.checked) {
                                    target = getEBid("64_A_keytext2");
                                }
                                else 
                                    if (mark3.checked) {
                                        target = getEBid("64_A_keytext3");
                                    }
                                    else 
                                        if (mark4.checked) {
                                            target = getEBid("64_A_keytext4");
                                        }
                            
                            if (target.value.length != 5) {
                                return err_length();
                            }
                            else {
                                return true;
                            }
                        }
                }
                if (keylength128.checked == true) {
                    if (keytypeManual.checked == true) {
                        var mark1 = getEBid("128_m_key1");
                        var mark2 = getEBid("128_m_key2");
                        var mark3 = getEBid("128_m_key3");
                        var mark4 = getEBid("128_m_key4");
                        if (mark1.checked) {
                            target = getEBid("128_m_keytext1");
                        }
                        else 
                            if (mark2.checked) {
                                target = getEBid("128_m_keytext2");
                            }
                            else 
                                if (mark3.checked) {
                                    target = getEBid("128_m_keytext3");
                                }
                                else 
                                    if (mark4.checked) {
                                        target = getEBid("128_m_keytext4");
                                    }
                        if (setHex(target.value) == false) {
                            return false;
                        }
                        if (target.value.length != 26) {
                            return err_length();
                        }
                        else {
                            return setHex(target.value);
                        }
                    }
                    else 
                        if (keytypeAscii.checked == true) {
                            var mark1 = getEBid("128_a_key1");
                            var mark2 = getEBid("128_a_key2");
                            var mark3 = getEBid("128_a_key3");
                            var mark4 = getEBid("128_a_key4");
                            if (mark1.checked) {
                                target = getEBid("128_A_keytext1");
                            }
                            else 
                                if (mark2.checked) {
                                    target = getEBid("128_A_keytext2");
                                }
                                else 
                                    if (mark3.checked) {
                                        target = getEBid("128_A_keytext3");
                                    }
                                    else 
                                        if (mark4.checked) {
                                            target = getEBid("128_A_keytext4");
                                        }
                            
                            if (target.value.length != 13) {
                                return err_length();
                            }
                            else {
                                return true;
                            }
                        }
                }
            }
}
