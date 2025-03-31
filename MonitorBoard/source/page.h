R"(
<!DOCTYPE html>
<html lang='en'>

<head>
	<meta charset='UTF-8'>
	<meta name='viewport' content='width=device-width, initial-scale=1.0'>
	<meta http-equiv='X-UA-Compatible' content='ie=edge'>
	<title>MonitorBoard</title>
	<style>
		* {
			margin: 0;
			padding: 0;
		}

		#main {
			height: 96vh;
			width: 96%;
			background-color: #F5F4F4;
			position: relative;
			padding: 2vh 2%;
		}

		body {
			font-family: Circular, -apple-system, BlinkMacSystemFont, Roboto, 'Helvetica Neue', sans-serif;
			font-size: 16px;
			font-weight: 600;
			line-height: 20px;
			display: flex;
			align-items: center;
			justify-content: center;
			background-color: #FFFFFF;
		}

		#nav {
			max-width: 100%;
			padding: 5px;
		}

		#preview {
			max-width: 96%;
			border: 2px solid #000000;
			border-radius: 8px;
			padding: 2%;
			overflow-wrap: break-word;
			word-wrap: break-word;
			hyphens: auto;
		}

		#previewNoticeHeader {
			padding-bottom: 2%;
			width: 100%;
		}

		#previewNoticeBody {
			padding-top: 2%;
			width: 100%;
			display: -webkit-box;
			-webkit-line-clamp: 6;
			-webkit-box-orient: vertical;
			overflow: hidden;
			text-overflow: ellipsis;
		}

		.box {
			background-color: #FFFFFF;
			border: 1px solid #222222;
			border-radius: 8px;
			box-sizing: border-box;
			color: #222222;
			display: flex;
			margin: 0;
			outline: none;
			padding: 10px;
			position: relative;
			text-decoration: none;
			touch-action: manipulation;
			transition: box-shadow .2s, -ms-transform .1s, -webkit-transform .1s, transform .1s;
			user-select: none;
			-webkit-user-select: none;
			width: 100%;
		}

		.box:focus-visible {
			box-shadow: #222222 0 0 0 2px, rgba(255, 255, 255, 0.8) 0 0 0 4px;
			transition: box-shadow .2s;
		}

		.box:active {
			background-color: #F7F7F7;
			border-color: #000000;
			transform: scale(.96);
		}

		.box:disabled {
			border-color: #DDDDDD;
			color: #DDDDDD;
			cursor: not-allowed;
			opacity: 1;
		}

		.box:hover {
			background-color: #F7F7F7;
			border-color: #000000;
		}

		@media (hover:hover) {
			.box {
				cursor: pointer;
			}
		}

		@media (hover: none) {
			.box {
				cursor: none;
			}
		}

		@media (max-width: 700px) {
			#main {
				width: 100%;
			}
		}

		@media (min-width: 700px) {
			#main {
				width: 40%;
			}
		}

		#btnUpdate {
			display: flex;
			justify-content: center;
		}

		.noticeInputBox {
			white-space: nowrap;
			overflow: hidden;
			text-overflow: ellipsis;
		}

		/* Modal Styling */
		.modal {
			display: none;
			position: absolute;
			/* Changed from fixed */
			top: 50%;
			left: 50%;
			transform: translate(-50%, -50%);
			background-color: rgba(0, 0, 0, 0.5);
			width: 100%;
			height: 100%;
			justify-content: center;
			align-items: center;
		}

		.modal-content {
			background-color: #FFFFFF;
			border-radius: 8px;
			padding: 20px;
			width: 80%;
			/* Adjusted width */
			box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
		}

		.modal-header {
			font-size: 18px;
			font-weight: bold;
			margin-bottom: 10px;
			display: flex;
			justify-content: space-between;
			align-items: center;
		}

		.modal-body input,
		.modal-body textarea {
			width: 100%;
			padding: 10px;
			border: 1px solid #222222;
			border-radius: 8px;
			font-size: 16px;
			font-family: inherit;
			box-sizing: border-box;
			outline: none;
		}

		.modal-body textarea {
			resize: none;
		}

		.modal-footer {
			display: flex;
			justify-content: flex-end;
			margin-top: 20px;
		}

		.modal-footer button {
			background-color: #222222;
			color: #FFFFFF;
			border: none;
			padding: 10px 20px;
			border-radius: 8px;
			cursor: pointer;
			font-size: 14px;
		}

		.modal-footer button:hover {
			background-color: #444444;
		}
	</style>
</head>

<body>
	<div id="main">
		<div id='nav'>
			<center>
				<h2>MonitorBoard</h2>
				<p>
					v1.0
				</p>
			</center>
		</div>
		<hr><br>
		<div id='preview'>
			<h3 id='previewNoticeHeader'>Notice Header</h3>
			<hr>
			<p id='previewNoticeBody'>
				Notice Body
			</p>
		</div>
		<br>
		<div id='options'>
			<div class='box' id='noteHeaderBox'>
				<div style='min-width: 95%;'>
					<h4>Note Header</h4>
					<p class='noticeInputBox'>
						Add a Note Header
					</p>
				</div>
				<p style='display:flex; align-items: center; min-width: 5%; min-height: 100%;'>
					>
				</p>
			</div>
			<br>
			<div class='box' id='noteBodyBox'>
				<div style='min-width: 95%;'>
					<h4>Note Body</h4>
					<p class='noticeInputBox'>
						Add a Note Body
					</p>
				</div>
				<p style='display:flex; align-items: center; min-width: 5%; min-height: 100%;'>
					>
				</p>
			</div>
			<br>
			<button class='box' id='btnUpdate'>UPDATE</button>
		</div>

		<!-- Modal -->
		<div class='modal' id='inputModal'>
			<div class='modal-content'>
				<div class='modal-header' id='modalHeader'>
					<span id="dialogHeader">Edit</span>
					<span id="close">×</span>
				</div>
				<div class='modal-body'>
					<input type='text' id='modalInputField' placeholder='Add a Note Header...' style='display: none;'>
					<textarea id='modalTextAreaField' rows='4' placeholder='Add a Note Body...'
						style='display: none;'></textarea>
				</div>
				<div class='modal-footer'>
					<button id='saveButton'>Save</button>
				</div>
			</div>
		</div>
	</div>
	<script>
		document.addEventListener('DOMContentLoaded', () => {
			const noteHeaderBox = document.getElementById('noteHeaderBox');
			const noteBodyBox = document.getElementById('noteBodyBox');
			const btnUpdate = document.getElementById('btnUpdate');
			const dialogHeader = document.getElementById('dialogHeader');
			const close = document.getElementById('close');
			const modal = document.getElementById('inputModal');
			const modalHeader = document.getElementById('modalHeader');
			const modalInputField = document.getElementById('modalInputField');
			const modalTextAreaField = document.getElementById('modalTextAreaField');
			const saveButton = document.getElementById('saveButton');
			const previewNoticeHeader = document.getElementById('previewNoticeHeader');
			const previewNoticeBody = document.getElementById('previewNoticeBody');

			let isHeader = true; // Track if editing header or body

			// Show modal when clicking on boxes
			noteHeaderBox.addEventListener('click', () => {
				isHeader = true;
				dialogHeader.textContent = 'Edit Note Header';
				modalInputField.style.display = 'block';
				modalTextAreaField.style.display = 'none';

				// Set input value only if preview is not empty
				if (previewNoticeHeader.textContent.trim() == 'Notice Header') {
					modalInputField.value = '';
				} else {
					modalInputField.value = previewNoticeHeader.textContent.trim();
				}
				modal.style.display = 'flex';
			});

			noteBodyBox.addEventListener('click',
				() => {
					isHeader = false;
					dialogHeader.textContent = 'Edit Note Body';
					modalInputField.style.display = 'none';
					modalTextAreaField.style.display = 'block';

					// Set textarea value only if preview is not empty
					if (previewNoticeBody.textContent.trim() == 'Notice Body') {
						modalTextAreaField.value = '';
					} else {
						modalTextAreaField.value = previewNoticeBody.textContent.trim();
					}
					modal.style.display = 'flex';
				});

			btnUpdate.addEventListener('click', () => {
				const value1 = document.getElementById('previewNoticeHeader').innerText;
        const value2 = document.getElementById('previewNoticeBody').innerText;
          const xhr = new XMLHttpRequest();
          xhr.open("POST", "/text", true);
          xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
          xhr.onreadystatechange = function () {
              if (xhr.readyState === 4) {
                    if (xhr.status === 200) {
                      alert("Data Sent Successfully!");
                    } else {
                      alert("Error Sending Data.");
                  }
                }
              };
            xhr.send("value1=" + encodeURIComponent(value1) + "&value2=" + encodeURIComponent(value2));
			});   

			// Save changes and update preview
			saveButton.addEventListener('click',
				() => {
					if (isHeader) {
						previewNoticeHeader.textContent = modalInputField.value.trim() || 'Notice Header';
					} else {
						previewNoticeBody.textContent = modalTextAreaField.value.trim() || 'Notice Body';
					}
					modal.style.display = 'none';
				});

			// Close modal when clicking the close button
			close.addEventListener('click', () => {
				modal.style.display = 'none';
			});
		});
	</script>
</body>

</html>
)"