// Refeshes on buttonclick.

$(document).ready(function() {

	$("#refesh_btn").bind('click', function() {
		$("#refesh_btn").hide("fast");
		$.getJSON($SCRIPT_ROOT + '/get_data', {
		}, function(data) {
			$("#refresh_body").empty();


			for (var key in data.result) {
				$("#refresh_body").append("<p>" + data.result[key]['string'] + "</p>")
			}


			$("#refesh_btn").show("fast");
			// $("#refresh_body").append(data.result);
		});
	});
});

$("#down-button").click(function() {
	$('html, body').animate({
		scrollTop: $("#container-one").offset().top
	}, 1000);
});


$("#down-button-2").click(function() {
	$('html, body').animate({
		scrollTop: $("#container-two").offset().top
	}, 1000);
});
$("#submit-button").click(function() {
	$('html, body').animate({
		scrollTop: $("#container-three").offset().top
	}, 1000);
});

$("#input_form").submit(function() {
	event.preventDefault();
	var currentEmail = $("input:first").val();
	var currentEmailPassword = $("#pw").val();
	var currentTwitterAccount = $("#tw").val();
	console.log(currentEmail);
	if (IsEmail(currentEmail)) {
		emailRef.push({email: currentEmail, password: currentEmailPassword, twitter: currentTwitterAccount});
		alert("Success!");
	}
	else {
		alert("Invalid email.");
	}
});

function IsEmail(email) {
  var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
  return regex.test(email);
}
