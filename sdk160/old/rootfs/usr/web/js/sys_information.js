/// <reference path="en-US.js" />
/// <reference path="jquery-1.10.2.min.js" />


function uptime2str(seconds) {
    var day_unit = 24 * 60 * 60;
    var hour_unit = 60 * 60;
    var min_unit = 60;
    var day = 0;
    var hour = 0;
    var min = 0;
    var len = 0;
    var ret = "";
    if (seconds < 60) {
        ret += 1 + Information_minute;
        return ret;
    }
    day = seconds / day_unit;
    seconds %= day_unit;
    hour = seconds / hour_unit;
    seconds %= hour_unit;
    min = seconds / min_unit;
    day = parseInt(day);
    hour = parseInt(hour);
    min = parseInt(min);
    if (day > 0)
        ret += day + Information_day;
    if (hour > 0)
        ret += hour + Information_hour;
    if (min > 0 || ret.length == 0)
        ret += min + Information_minute;

    return ret;
}

function initial_language() {

    $("#information-page-title").text(Information_title);

    //versions
    $("#versions").text(Information_version);
    $("#version-platform-title").text(Information_platform);
    $("#version-platform-value").text(Information_platform_version);
    $("#version-fw-title").text(Information_firmware);
    $("#version-fw-value").text(Information_firmware_version);
    $("#version-kernel-title").text(Information_kernel);
    $("#version-kernel-value").text(Information_kernel_version);
    $("#version-serialNumber-title").text(Information_serial);
    $("#version-serialNumber-value").text(Information_serial_num);
    $("#version-rootfs-title").text(Information_rootfs);
    $("#version-rootfs-value").text(Information_rootfs_version);
    $("#version-uboot-title").text(Information_uboot);
    $("#version-uboot-value").text(Information_uboot_version);

    //addresses
    $("#addresses").text(Information_ip_mac);
    $("#address-ip-title").text("eth0");
    $("#address-ip-value").text(Information_ip_str);
    $("#address-mac-title").text("MAC");
    $("#address-mac-value").text(Information_ip_mac_str);

    //date-time
    $("#date-time").text(Information_date_time);
    $("#date-currentTime-title").text(Information_current_time);
    $("#date-currentTime-value").text(Information_current_time_str);
    $("#date-upTime-title").text(Information_uptime);
    $("#date-upTime-value").text(uptime2str(uptime_seconds));

    //sdcard-info
    $("#sdcard-info").text(Information_disk);
    $("#sdcard-total-title").text(Information_disk_size);
    $("#sdcard-total-value").text(Information_disk_size_str);
    $("#sdcard-used-title").text(Information_disk_used);
    $("#sdcard-used-value").text(Information_disk_used_str);
    $("#sdcard-available-title").text(Information_disk_available);
    $("#sdcard-available-value").text(Information_disk_available_str);

    //memery-info
    $("#memery-info").text(Information_mem);
    $("#memery-total-title").text(Information_mem_total);
    $("#memery-total-value").text(Information_mem_total_str);
    $("#memery-free-title").text(Information_mem_free);
    $("#memery-free-value").text(Information_mem_free_str);
    $("#memery-available-title").text(Information_mem_used);
    $("#memery-available-value").text(Information_mem_used_str);
}

$(function () {
    initial_language();
});