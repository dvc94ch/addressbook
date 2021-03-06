;;; Copyright © 2016 David Craven <david@craven.ch>
;;;
;;; This file is part of AddressBook.
;;;
;;; This program is free software: you can redistribute it and/or modify it
;;; under the terms of the GNU General Public License as published by
;;; the Free Software Foundation, either version 3 of the License, or (at
;;; your option) any later version.
;;;
;;; This program is distributed in the hope that it will be useful, but
;;; WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with GNU Guix.  If not, see <http://www.gnu.org/licenses/>.

(use-modules (guix)
             (guix build-system gnu)
             ((guix licenses) #:prefix license:)
             (gnu packages autotools)
             (gnu packages check)
             (gnu packages commencement)
             (gnu packages gdb)
             (gnu packages linux)
             (gnu packages pkg-config)
             (gnu packages texinfo)
             (gnu packages valgrind))

(define-public addressbook
  (package
    (name "addressbook")
    (version "0.1")
    (source #f)
    (build-system gnu-build-system)
    (home-page "https://github.com/dvc94ch/addrbook")
    (synopsis "Address book")
    (description "Command line application for managing contact information.")
    (license license:gpl3+)))

(package
  (inherit addressbook)
  (native-inputs
   `(("autoconf" ,autoconf)
     ("automake" ,automake)
     ("check" ,check)
     ("gdb" ,gdb)
     ("libtool" ,libtool)
     ("pkg-config" ,pkg-config)
     ("strace" ,strace)
     ("texinfo" ,texinfo)
     ("valgrind" ,valgrind))))
