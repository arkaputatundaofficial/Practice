const passLock = document.getElementById("passLock"); // icon
const passInput = document.getElementById("password"); // input
const emailInput = document.getElementById("email"); // email input
const loginBtn = document.getElementById("login"); // login button
let isLocked = true;

passLock.addEventListener("click", function () {
    if (isLocked) {
    passLock.className = "fa-solid fa-unlock";
    passInput.type = "text";
    isLocked = false;
  } else {
    passLock.className = "fa-solid fa-lock";
    passInput.type = "password";
    isLocked = true;
  }
});

loginBtn.addEventListener("click", function (e) {
    e.preventDefault();
    const email = emailInput.value.trim();
    const password = passInput.value.trim();

    if (email === "" || password === "") {
        alert("Please fill in all fields.");
    } else if (email === "arkaputatunda2@gmail.com" && password === "qwerty") {
        alert("Login successful!");
        location.href = "landing-page/index.html";
    } else {
        alert("Invalid email or password.");
    }
});
