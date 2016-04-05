;; author: Tao Liu. This is an individual assignment.

;;; (gen-list start stop). This function generates a list of consecutive integers, from start to stop
;;; This is an eager approach to generate list
(define gen-list
  (lambda (start stop)
    ;;base case
    (if (> start stop)
        '();return an empty list
        ;;else
        (cons start (gen-list (+ start 1) stop)))))

;;; (pair-sum? list val). This function tests whether any two adjacent values in numlist sum to val.
(define pair-sum?
  (lambda (lst val)
    (if (< (length lst) 2); base case, when there is less than 2 elements in the list, return false
        #f
        (let ([x (car lst)]; assign the first element in the lst to x
              [y (car (cdr lst))]); assign the second element in the lst to y
          (let ([truth (equal? val (+ x y))]); assign the truth value of (x + y) == val to truth
            (or truth (pair-sum? (cdr lst) val)))))))

;;; (gen-lazy-list start stop). This function generates a list of consecutive integers, from start to stop, lazily.
;;; given out in the assignment prompt
(define gen-lazy-list
  (lambda (start stop)
    (if (> start stop)
        #f
        (cons start
            (lambda () (gen-lazy-list (+ start 1) stop))))))

;;; (pair-sum-lazy? (gen-lazy-list start stop) val). This function does the same thing as the pair-sum? I wrote above, but to a lazylist
(define pair-sum-lazy?
  (lambda (lazylist val)
    (if (not (and lazylist ((cdr lazylist)))); base case, when there is less than 2 elements in the list, return false
        #f
        (let ([x (car lazylist)]; assign the first element in the lst to x
              [y (car ((cdr lazylist)))]); assign the second element in the lst to y
          (let ([truth (equal? val (+ x y))]); assign the truth value of (x + y) == val to truth
            (or truth (pair-sum-lazy? ((cdr lazylist)) val)))))))


    
                        