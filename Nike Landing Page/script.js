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

loginBtn.addEventListener("click", function () {
    const email = emailInput.value;
    const password = passInput.value;
    
    if (email == "arkaputatunda2@gmail.com" && password == "qwerty") {
        window.location.href = "../landing-page/index.html";
        alert("Login successful!");
    } else if (email == "" || password == "") {
        alert("Please fill in all fields.");
    } else {
        alert("Invalid email or password.");
    }
});