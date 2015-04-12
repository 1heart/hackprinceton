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
$("#down-button-3").click(function() {
	$('html, body').animate({
		scrollTop: $("#container-three").offset().top
	}, 1000);
});