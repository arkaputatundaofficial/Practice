const current_time = document.getElementById("current_time");

function startTime() {
  const today = new Date();
  let h = today.getHours();
  let m = today.getMinutes();
  let s = today.getSeconds();
  let ampm = h >= 12 ? "PM" : "AM";

  h = h % 12;
  h = h ? h : 12; // hour '0' should be '12'

  m = checkTime(m);
  s = checkTime(s);

  current_time.innerHTML = `${h}:${m}:${s} ${ampm}`;
}

function checkTime(i) {
  return i < 10 ? "0" + i : i;
}
setInterval(startTime, 1000);
