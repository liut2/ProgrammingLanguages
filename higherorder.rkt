;; author: Tao Liu and Duo Tao
;; higherorder.rkt

;;; Define a function curry3 that takes a three-argument function and
;;; returns a curried version of that function
(define curry3
  (lambda (func)
    (lambda (x)
      (lambda (y)
        (lambda (z)
          (func x y z))))))

;;; Define a function uncurry3 that takes a curried three-argument function and
;;; returns a normal Scheme uncurried version of that function.
(define uncurry3
  (lambda (func)
    (lambda (x y z)
      (((func x) y) z))))

;;; Define a function called my-filter that works just like filter does,
;;; but doesn't use filter or any other higher-order functions.
(define my-filter
  (lambda (pred lst)
    (cond ((null? lst) lst) ; base case
          ;; if current item satisfies pred, add to the result
          ((pred (car lst)) (cons (car lst) (my-filter pred (cdr lst))))
          ;; if not, don't include it in result
          (else (my-filter pred (cdr lst))))))

;;; (union S1 S2) handles S1 and S2 as sets and return their union
(define union
  (lambda (set1 set2)
    (append set1 (my-filter (union-helper set1) set2))))

;;; Helper function for the union method
;;; Returns the curried function to check if element is in lst
(define union-helper
  (lambda (lst)
    (lambda (element)
      (if (member element lst)
          #f ; for ease of use, return false if exists
          #t)))) ; return true if not

;;; (intersect S1 S2) handles S1 and S2 as sets and return their intersection
(define intersect
  (lambda (set1 set2)
    (my-filter (intersect-helper set1) set2)))

;;; Helper function for the intersect method
;;; Returns the curried function to check if element is in lst
(define intersect-helper
  (lambda (lst)
    (lambda (element)
      (if (member element lst)
          #t
          #f))))

;;; (exists pred lst) returns #t if at least one item in a list satisfies a pred.
(define exists
  (lambda (pred lst)
    (if (null? (my-filter pred lst))
        #f
        #t)))
