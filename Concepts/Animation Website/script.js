alert('Hello World!');
let cards = document.querySelectorAll(".card");
let index = 0;
let totalCards = cards.length;

function updateCarousel() {
    // Hide all cards
    cards.forEach(card => card.style.display = "none");

    // Show the current pair of cards
    cards[index].style.display = "flex";
    cards[(index + 1) % totalCards].style.display = "flex"; // Ensures looping back

    // Update index for next iteration
    index = (index + 2) % totalCards;
}

// Run the function every second
setInterval(updateCarousel, 1000);

// Initial display
updateCarousel();
