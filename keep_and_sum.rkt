;;answer to question 4
(define keep-first-n
  (lambda (num L)
    (if (< num 0)
        "negative!"
        (if (> num (length L))
            "too large!"
            (if (= num 0)
                '()
                (append (list (car L))
                        (keep-first-n (- num 1) (cdr L))))))))
;;answer to question 5
(define sum
  (lambda (L)
    (if (null? L)
        0
        (+ (car L) (sum (cdr L))))))

                