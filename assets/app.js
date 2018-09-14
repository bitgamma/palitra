let scrollableLinks = document.querySelectorAll('.app__menu-item-link');

function smoothScrollToLink(e) {
  let hashPos = this.href.indexOf('#');
  let hash = this.href.substr(hashPos);
  let el = document.querySelector(hash);

  if (typeof (this.href) !== 'string') {
    return;
  }

  if (hashPos === -1) {
    return;
  }

  if (!el) {
    return;
  }

  e.preventDefault();

  el.scrollIntoView({
    behavior: 'smooth',
    block: 'start'
  });
}

document.getElementById("mobile-menu").addEventListener("click", (e) => {
  if(document.getElementById("menu").classList.contains("app__mobile-hide")) {
    document.getElementById("menu").classList.remove("app__mobile-hide");
  } else {
    document.getElementById("menu").classList.add("app__mobile-hide");
  }
  e.preventDefault;
});

scrollableLinks.forEach(link => {
  link.addEventListener('click', smoothScrollToLink);
});
