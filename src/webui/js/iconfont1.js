!function (l) {
    var e,
        d = '<svg><symbol id="icon-xiala" viewBox="0 0 1024 1024"><path d="M824.32 328.96c-12.8-12.8-33.28-12.8-45.44 0L481.92 624 183.68 328.96c-12.8-12.8-33.28-12.8-45.44 0-12.8 12.16-12.8 32.64 0 45.44l317.44 314.24c1.28 1.28 1.28 3.2 2.56 4.48 12.8 12.8 33.28 12.8 45.44 0l320-318.08C837.12 362.24 837.12 341.76 824.32 328.96z"  ></path></symbol></svg>',
        t = (e = document.getElementsByTagName("script"))[e.length - 1].getAttribute("data-injectcss");
    if (t && !l.__iconfont__svg__cssinject__) {
        l.__iconfont__svg__cssinject__ = !0;
        try {
            document.write("<style>.svgfont {display: inline-block;width: 1em;height: 1em;fill: currentColor;vertical-align: -0.1em;font-size:16px;}</style>")
        } catch (e) {
            console && console.log(e)
        }
    }
    !function (e) {
        if (document.addEventListener) if (~["complete", "loaded", "interactive"].indexOf(document.readyState)) setTimeout(e, 0); else {
            var t = function () {
                document.removeEventListener("DOMContentLoaded", t, !1), e()
            };
            document.addEventListener("DOMContentLoaded", t, !1)
        } else document.attachEvent && (n = e, o = l.document, i = !1, c = function () {
            i || (i = !0, n())
        }, (d = function () {
            try {
                o.documentElement.doScroll("left")
            } catch (e) {
                return void setTimeout(d, 50)
            }
            c()
        })(), o.onreadystatechange = function () {
            "complete" == o.readyState && (o.onreadystatechange = null, c())
        });
        var n, o, i, c, d
    }(function () {
        var e, t, n, o, i, c;
        (e = document.createElement("div")).innerHTML = d, d = null, (t = e.getElementsByTagName("svg")[0]) && (t.setAttribute("aria-hidden", "true"), t.style.position = "absolute", t.style.width = 0, t.style.height = 0, t.style.overflow = "hidden", n = t, (o = document.body).firstChild ? (i = n, (c = o.firstChild).parentNode.insertBefore(i, c)) : o.appendChild(n))
    })
}(window);