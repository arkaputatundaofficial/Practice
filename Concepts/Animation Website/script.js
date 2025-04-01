var carousel = document.querySelector(".carousel");
var seats = Array.from(document.querySelectorAll(".carousel-seat"));
var prevButton = document.querySelector(".prev");
var nextButton = document.querySelector(".next");

function next(el) {
  let index = seats.indexOf(el);
  return index < seats.length - 1 ? seats[index + 1] : seats[0];
}

function prev(el) {
  let index = seats.indexOf(el);
  return index > 0 ? seats[index - 1] : seats[seats.length - 1];
}

function progress() {
  var el = document.querySelector(".is-ref");
  el.classList.remove("is-ref");
  var newSeat = next(el);

  newSeat.classList.add("is-ref");
  newSeat.style.order = 1;

  let order = 2;
  let tempSeat = newSeat;
  for (let i = 1; i < seats.length; i++) {
    tempSeat = next(tempSeat);
    tempSeat.style.order = order++;
  }

  carousel.classList.remove("is-set");
  setTimeout(() => carousel.classList.add("is-set"), 50);
}

// Progress on Next Button Click
nextButton.addEventListener("click", () => {
  progress();
});

// Progress on Previous Button Click
prevButton.addEventListener("click", () => {
  var el = document.querySelector(".is-ref");
  el.classList.remove("is-ref");
  var newSeat = prev(el);

  newSeat.classList.add("is-ref");
  newSeat.style.order = 1;

  let order = 2;
  let tempSeat = newSeat;
  for (let i = 1; i < seats.length; i++) {
    tempSeat = prev(tempSeat);
    tempSeat.style.order = order++;
  }

  carousel.classList.remove("is-set");
  setTimeout(() => carousel.classList.add("is-set"), 50);
});

document.addEventListener("DOMContentLoaded", async function () {
  const carouselSeats = document.querySelectorAll(".carousel-seat");
  const apiUrl = "https://picsum.photos/v2/list?page=2&limit=10";

  try {
    const response = await fetch(apiUrl);
    const images = await response.json();

    images.forEach((image, index) => {
      if (carouselSeats[index]) {
        const img = document.createElement("img");
        img.src = image.download_url;
        img.alt = `Image by ${image.author}`;
        img.style.width = "100%";
        img.style.height = "auto";

        carouselSeats[index].innerHTML = ""; // Clear existing content
        carouselSeats[index].appendChild(img);
      }
    });
  } catch (error) {
    console.error("Error fetching images:", error);
  }
});

const colors = ["#220E6F", "#A82998", "#E92B60", "#FAE519", "#52C790", "#4870C2"];
let index = 0;

function getContrastColor(hex) {
  // Convert hex to RGB
  let r = parseInt(hex.substr(1, 2), 16);
  let g = parseInt(hex.substr(3, 2), 16);
  let b = parseInt(hex.substr(5, 2), 16);
  
  // Calculate luminance
  let luminance = (0.299 * r + 0.587 * g + 0.114 * b) / 255;
  
  // Return black or white depending on luminance
  return luminance > 0.5 ? "#000000" : "#ffffff";
}

function changeBackground() {
  const div = document.getElementById("thankYou");
  div.style.backgroundColor = colors[index];
  div.style.color = getContrastColor(colors[index]);
  
  index = (index + 1) % colors.length;
}

setInterval(progress, 2000);
setInterval(changeBackground, 1000);
