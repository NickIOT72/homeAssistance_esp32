var credData = {
    "ssid": "",
    "password": ""
}

$(document).ready(function() {

    $("#credentials").on("change", function(event) {
        credData.ssid = this.value;
        console.log("ssid:", credData.ssid);
        validationInfo($("#credentials"));
        updateStatus();
    })

    $("#pwd").on("change", function(event) {
        credData.password = this.value;
        console.log("password:", credData.password);
        validationInfo($("#pwd"));
        updateStatus();
    });

    $("#submitBtn").on("click", function(event) {
        event.preventDefault();
        // submit form with credentials
        let objCredentials = {
            "ssid": $('#credentials').find(":selected").val(),
            "password": $("#pwd").val(),
        }
        $("#credentials").prop('disabled', 'disabled');
        if (!$("#credentials").hasClass("select-disabled")) $("#credentials").addClass("select-disabled");
        $("#pwd").prop('disabled', 'disabled');
        if (!$("#pwd").hasClass("select-disabled")) $("#pwd").addClass("select-disabled");
        disableSubmitButton();
        sendCredentialsToServer(objCredentials);
        //changeStatusLabel("Credentials sent. Waiting for connecttion <br/> Verify if led of ESP32 starts blinking", true, $("#statusLabel"));
    })


    //webSocketEvent();
    //requestWiFiCredentials();
});

function disableForm() {
    $("#credentials").prop('disabled', 'disabled');
    if (!$("#credentials").hasClass("select-disabled")) $("#credentials").addClass("select-disabled");
    $("#pwd").prop('disabled', 'disabled');
    if (!$("#pwd").hasClass("select-disabled")) $("#pwd").addClass("select-disabled");
    disableSubmitButton();
}

function enableForm() {
    $("#credentials").prop('disabled', false);
    if ($("#credentials").hasClass("select-disabled")) $("#credentials").removeClass("select-disabled");
    $("#pwd").prop('disabled', false);
    if ($("#pwd").hasClass("select-disabled")) $("#pwd").removeClass("select-disabled");
    allowSubmitButton();
}

function requestWiFiCredentials() {
    disableForm();
    $("#statusLabel").text("Waiting for wifi credentials...");
    sendReqOFWiFiCredentials();
}

function changeStatusLabel(text, opt, cred) {
    cred.text(text);
    if (opt) {
        if (cred.hasClass("status-wrong")) cred.removeClass("status-wrong");
        if (!cred.hasClass("status-valid")) cred.addClass("status-valid");
    } else {
        if (cred.hasClass("status-valid")) cred.removeClass("status-valid");
        if (!cred.hasClass("status-wrong")) cred.addClass("status-wrong");
    }
}

function updateStatus() {
    if ($("#credentials").hasClass("valid-data") && $("#pwd").hasClass("valid-data")) {
        changeStatusLabel("Ready to submit", true, $("#statusLabel"));
        allowSubmitButton();
    } else if ($("#credentials").hasClass("valid-data") && $("#pwd").hasClass("wrong-data")) {
        changeStatusLabel("Verify Password", false, $("#statusLabel"));
        disableSubmitButton();
    } else if ($("#credentials").hasClass("wrong-data") && $("#pwd").hasClass("valid-data")) {
        changeStatusLabel("Select SSID", false, $("#statusLabel"));
        disableSubmitButton();
    } else if ($("#credentials").hasClass("wrong-data") && $("#pwd").hasClass("wrong-data")) {
        changeStatusLabel("Select SSID and verify password", false, $("#statusLabel"));
        disableSubmitButton();
    }
}

function allowSubmitButton() {
    let cred = $("#submitBtn");
    cred.prop("disabled", false);
    if (cred.hasClass("button-disable")) cred.removeClass("button-disable");
    if (!cred.hasClass("button-enable")) cred.addClass("button-enable");
}

function disableSubmitButton() {
    let cred = $("#submitBtn");
    cred.prop("disabled", true);
    if (cred.hasClass("button-enable")) cred.removeClass("button-enable");
    if (!cred.hasClass("button-disable")) cred.addClass("button-disable");
}

function validationInfo(cred) {

    if (cred.val()) {
        if (cred.hasClass("wrong-data")) cred.removeClass("wrong-data");
        if (!cred.hasClass("valid-data")) cred.addClass("valid-data");
    } else {
        if (cred.hasClass("valid-data")) cred.removeClass("valid-data");
        if (!cred.hasClass("wrong-data")) cred.addClass("wrong-data");
    }

}

let verifyCred = () => {
    return (credData.ssid && credData.password);
};

$('.form').find('input, textarea').on('keyup blur focus', function(e) {

    var $this = $(this),
        label = $this.prev('label');

    if (e.type === 'keyup') {
        if ($this.val() === '') {
            label.removeClass('active highlight');
        } else {
            label.addClass('active highlight');
        }
    } else if (e.type === 'blur') {
        if ($this.val() === '') {
            label.removeClass('active highlight');
        } else {
            label.removeClass('highlight');
        }
    } else if (e.type === 'focus') {

        if ($this.val() === '') {
            label.removeClass('highlight');
        } else if ($this.val() !== '') {
            label.addClass('highlight');
        }
    }

});

$('.tab a').on('click', function(e) {

    e.preventDefault();

    $(this).parent().addClass('active');
    $(this).parent().siblings().removeClass('active');

    target = $(this).attr('href');

    $('.tab-content > div').not(target).hide();

    $(target).fadeIn(600);

});