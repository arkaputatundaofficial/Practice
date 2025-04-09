let alarmTime = null;
let alarmTriggered = false;
let selectedHour = null;
let selectedMinute = null;

const timepickerContainer = document.getElementById('timepicker');
const timePicker = new tui.TimePicker(timepickerContainer, {
    inputType: 'spinbox',
    initialHour: 6,
    initialMinute: 0,
    showMeridiem: true
});

function updateTime() {
    const now = new Date();
    const formatted = now.toLocaleTimeString([], {
        hour: '2-digit', minute: '2-digit', second: '2-digit'
    });
    document.getElementById('current-time').textContent = formatted;

    if (alarmTime) {
        const alarmDate = new Date();
        alarmDate.setHours(alarmTime.hour, alarmTime.minute, 0, 0);

        if (alarmDate < now) {
            alarmDate.setDate(alarmDate.getDate() + 1);
        }

        const diff = alarmDate - now;
        const seconds = Math.floor(diff / 1000) % 60;
        const minutesLeft = Math.floor(diff / (1000 * 60)) % 60;
        const hoursLeft = Math.floor(diff / (1000 * 60 * 60));

        document.getElementById('status').style.display = 'block';
        document.getElementById('status').textContent =
        `upcoming alarm in ${hoursLeft}h ${minutesLeft}m ${seconds}s`;

        if (diff <= 1000 && !alarmTriggered) {
            alarmTriggered = true;
            alert("⏰ Alarm Time!");
            clearAlarm();
        }
    } else {
        document.getElementById('status').style.display = 'none';
    }
}

function openEditor() {
    document.getElementById('editor').style.display = 'block';
}

function showModal() {
    document.getElementById('modal-overlay').style.display = 'flex';
}

document.getElementById('setTime').addEventListener('click', () => {
    selectedHour = timePicker.getHour();
    selectedMinute = timePicker.getMinute();

    const meridiem = selectedHour >= 12 ? 'PM': 'AM';
    const displayHour = selectedHour % 12 || 12;
    const paddedMinute = selectedMinute.toString().padStart(2, '0');
    document.getElementById('chosen-time').textContent = `Time: ${displayHour}:${paddedMinute} ${meridiem}`;

    document.getElementById('modal-overlay').style.display = 'none';
});

function saveAlarm() {
    if (selectedHour !== null && selectedMinute !== null) {
        alarmTime = {
            hour: selectedHour,
            minute: selectedMinute
        };
        alarmTriggered = false;
        document.getElementById('set-alarm-btn').disabled = true;
        document.getElementById('editor').style.display = 'none';
    } else {
        alert("Please select a time before saving.");
    }
}

function clearAlarm() {
    alarmTime = null;
    selectedHour = null;
    selectedMinute = null;
    document.getElementById('set-alarm-btn').disabled = false;
    document.getElementById('status').style.display = 'none';
    document.getElementById('chosen-time').textContent = "Time: not selected";
}

setInterval(updateTime, 1000);

// Allow modal close by background click
document.getElementById('modal-overlay').addEventListener('click', (e) => {
    if (e.target === document.getElementById('modal-overlay')) {
        document.getElementById('modal-overlay').style.display = 'none';
    }
});
